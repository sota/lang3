#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import sys
import glob
import json
sys.dont_write_bytecode = True

from doit.task import clean_targets
from utils.fmt import fmt
from utils.git import subs2shas
from utils.shell import call, rglob, which
from utils.version import SotaVersionWriter

DODO = 'dodo.py'
REPOROOT = os.path.dirname(os.path.abspath(__file__))
SUBMODS = subs2shas().keys()
BINDIR = fmt('{REPOROOT}/bin')
LIBDIR = fmt('{REPOROOT}/lib')
PYTHON = which('python2')
RPYTHON = 'src/pypy/rpython/bin/rpython'
SRCDIR = fmt('{REPOROOT}/src')
TARGET = 'target.py'
VERSION_JSON = 'src/version.json'

DOIT_CONFIG = {
    'verbosity': 2,
    'default_tasks': ['post'],
}

try:
    J = call('nproc')[1].strip()
except: #pylint: disable=bare-except
    J = 1

try:
    SOTA_VERSION = open('VERSION').read().strip()
except: #pylint: disable=bare-except
    try:
        SOTA_VERSION = call('git describe')[1].strip()
    except: #pylint: disable=bare-except
        SOTA_VERSION = 'UNKNOWN'

def globs(*paths):
    '''
    returns a set of all paths glob-matched
    '''
    return set([item for item in [glob.glob(path) for path in paths] for item in item])

def task_version():
    '''
    create version files from version.json template
    '''
    versionfiles = json.load(open(VERSION_JSON))
    for filename, contents in versionfiles.items():
        svw = SotaVersionWriter(filename, fmt(contents))
        yield {
            'name': filename,
            'actions': [svw.update],
            'uptodate': [svw.uptodate],
        }

def is_initd():
    return all([call(fmt('git config --get submodule.{submod}.url'), throw=False)[1] for submod in SUBMODS])

def task_init():
    '''
    run git submodule init on submods
    '''
    return {
        'actions': ['git submodule init ' + ' '.join(SUBMODS)],
        'targets': ['.git/config'],
        'uptodate': [is_initd],
    }

def task_submod():
    '''
    run git submodule update on submods
    '''
    for submod in SUBMODS:
        yield {
            'name': submod,
            'file_dep': [DODO],
            'task_dep': ['init'],
            'actions': [fmt('git submodule update {submod}')],
        }

def task_pre():
    '''
    tests to run before build
    '''
    return dict(
        actions=[
            fmt('PYTHONPATH={SRCDIR} py.test -s -vv test/pre/'),
        ],
    )

def task_libcli():
    '''
    build so libary for use as sota's commandline interface
    '''
    return {
        'file_dep': [DODO] + rglob('src/cli/*.{h,c,cpp}'),
        'task_dep': ['pre', 'submod:src/docopt'],
        'actions': [
            fmt('cd src/cli && make -j {J}'),
            fmt('install -C -D src/cli/libcli.so {LIBDIR}/libcli.so'),
        ],
        'targets': ['src/cli/test', fmt('{LIBDIR}/libcli.so')],
        'clean': [clean_targets],
    }

def task_build():
    '''
    build binary using rpython machinery
    '''
    return dict(
        task_dep=['pre', 'libcli'],
        actions=[
            fmt('mkdir -p {BINDIR}'),
            fmt('{PYTHON} -B {RPYTHON} --no-pdb --output {BINDIR}/sota {SRCDIR}/{TARGET}'),
        ],
    )

def task_post():
    '''
    tests to run after build
    '''
    return dict(
        task_dep=['build'],
        actions=[
            fmt('PYTHONPATH={SRCDIR} py.test -s -vv test/post/'),
        ],
    )

def task_tidy():
    '''
    clean submods and sota/lang repo
    '''
    yield {
        'name': 'sota/lang',
        'actions': ['git clean -xfd'],
    }
    for submod in SUBMODS:
        yield {
            'name': submod,
            'actions': [
                fmt('cd {submod} && git reset --hard HEAD && git clean -xfd')
            ],
        }
