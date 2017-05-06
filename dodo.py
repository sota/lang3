#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import sys
import json
sys.dont_write_bytecode = True

from doit.task import clean_targets
from utils.fmt import fmt
from utils.git import subs2shas
from utils.shell import call, rglob, globs, which
from utils.version import SotaVersionWriter

DODO = 'dodo.py'
COLM = 'bin/colm'
RAGEL = 'bin/ragel'
REPOROOT = os.path.dirname(os.path.abspath(__file__))
BINDIR = fmt('{REPOROOT}/bin')
LIBDIR = fmt('{REPOROOT}/lib')
PYTHON = which('python2')
RPYTHON = 'src/pypy/rpython/bin/rpython'
SRCDIR = fmt('{REPOROOT}/src')
TARGET = 'target.py'
VERSION_JSON = 'src/version.json'
PREDIR = 'tests/pre'
POSTDIR = 'tests/post'
SUBS2SHAS = subs2shas()

DOIT_CONFIG = {
    'verbosity': 2,
    'default_tasks': ['post'],
}

ENVS = ' '.join([
    'PYTHONPATH=.:src:src/pypy:$PYTHONPATH',
])

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

def task_version():
    '''
    create version files from version.json template
    '''
    versionfiles = json.load(open(VERSION_JSON))
    for filename, contents in versionfiles.items():
        svw = SotaVersionWriter(filename, fmt(contents))
        yield dict(
            name=filename,
            actions=[svw.update],
            uptodate=[svw.uptodate],
        )

def task_submod():
    '''
    run ensure git submodules are up to date
    '''
    SYMS = [
        '+',
        '-',
    ]
    for submod, sha1hash in SUBS2SHAS.items():
        yield dict(
            name=submod,
            actions=[
                fmt('git submodule update --init {submod}')
            ],
            uptodate=[all(map(lambda sym: not sha1hash.startswith(sym), SYMS))],
        )

def task_colm():
    '''
    build colm binary for use in build
    '''
    return dict(
        task_dep=['submod:src/colm'],
        actions=[
            'cd src/colm && autoreconf -f -i',
            fmt('cd src/colm && ./configure --prefix={REPOROOT}'),
            'cd src/colm && make && make install',
        ],
        #uptodate=[fmt('test -f {COLM}')],
        targets=[COLM],
        clean=[clean_targets],
    )

def task_ragel():
    '''
    build ragel binary for use in build
    '''
    return dict(
        task_dep=['submod:src/ragel', 'colm'],
        actions=[
            'cd src/ragel && autoreconf -f -i',
            fmt('cd src/ragel && ./configure --prefix={REPOROOT} --with-colm={REPOROOT} --disable-manual'),
            'cd src/ragel && make && make install',
        ],
        #uptodate=[fmt('test -f {RAGEL}')],
        targets=[RAGEL],
        clean=[clean_targets],
    )

def task_liblexer():
    '''
    build so libary for use as sota's lexer
    '''
    return dict(
        file_dep=['src/sota/lexer.py'] + rglob('src/lexer/*.{h,rl,c}'),
        task_dep=['ragel', 'version:src/cli/version.h'],
        actions=[
            fmt('cd src/lexer && LD_LIBRARY_PATH={REPOROOT}/lib make -j {J} RAGEL={REPOROOT}/{RAGEL}'),
            fmt('install -C -D src/lexer/liblexer.so {LIBDIR}/liblexer.so'),
        ],
        #uptodate=[fmt('test -f {LIBDIR}/liblexer.so')],
        #targets=['src/lexer/lexer.cpp', 'src/lexer/test', fmt('{LIBDIR}/liblexer.so')],
        targets=[fmt('{LIBDIR}/liblexer.so')],
        clean=[clean_targets],
    )

def task_test():
    '''
    tests to run before build
    '''
    return dict(
        task_dep=['version:src/sota/version.py', 'liblexer'],
        actions=[
            fmt('{ENVS} py.test -s -vv {PREDIR}'),
        ],
    )

def task_cov():
    '''
    run 'py.test --cov=<pyfile> {PREDIR}/<pyfile>'
    '''
    def hastests(pyfile):
        return os.path.exists(os.path.join(PREDIR, pyfile))
    excludes = [DODO]
    pyfiles = globs('src/*/*.py') - globs(*excludes)
    for pyfile in sorted(pyfiles, key=hastests):
        covcmd = 'py.test -s -vv --cov={pyfile} {PREDIR}/{pyfile}'
        msgcmd = 'echo "no tests found ({PREDIR}/{pyfile} to run coverage on {pyfile}"'
        yield dict(
            name=pyfile,
            task_dep=['submod', 'version:src/sota/version.py'],
            actions=[fmt(covcmd if hastests(pyfile) else msgcmd)],
        )

def task_lint():
    '''
    run pylint on all pyfiles
    '''
    excludes = ['src/doit/dodo.py']
    for pyfile in globs('*.py', 'src/*/*.py', fmt('{PREDIR}/*/*.py')) - globs(*excludes):
        yield dict(
            name=pyfile,
            task_dep=['submod', 'version:src/sota/version.py'],
            actions=[fmt('{ENVS} pylint -E -j4 --rcfile {PREDIR}/pylint.rc {pyfile}')],
        )

def task_pre():
    '''
    run pre tests: pytest, pycov and pylint
    '''
    return {
        'task_dep': ['test'],
        'actions': ['echo "sota pre tests successfully tested!"'],
    }

def task_libcli():
    '''
    build so libary for use as sota's commandline interface
    '''
    return dict(
        file_dep=[DODO] + rglob('src/cli/*.{h,c,cpp}'),
        task_dep=['pre', 'submod:src/docopt'],
        actions=[
            fmt('cd src/cli && make -j {J}'),
            fmt('install -C -D src/cli/libcli.so {LIBDIR}/libcli.so'),
        ],
        targets=['src/cli/test', fmt('{LIBDIR}/libcli.so')],
        clean=[clean_targets],
    )

def task_sota():
    '''
    build sota binary using rpython machinery
    '''
    return dict(
        file_dep=[
            DODO,
            fmt('{LIBDIR}/libcli.so'),
            fmt('{LIBDIR}/liblexer.so'),
        ] + rglob(fmt('{SRCDIR}/*.py')),
        task_dep=['pre', 'libcli', 'liblexer'],
        actions=[
            fmt('mkdir -p {BINDIR}'),
            fmt('{PYTHON} -B {RPYTHON} --no-pdb --output {BINDIR}/sota {SRCDIR}/{TARGET}'),
        ],
        targets=[fmt('{BINDIR}/sota')],
        clean=[clean_targets],
    )

def task_post():
    '''
    tests to run after build
    '''
    return dict(
        task_dep=['sota'],
        actions=[
            fmt('{ENVS} py.test -s -vv {POSTDIR}'),
        ],
    )

def task_rmcache():
    '''
    recursively delete python cache files
    '''
    return dict(
        actions=[
            'find . -depth -name __pycache__ -type d -exec rm -r "{}" \;',
            'find . -depth -name "*.pyc" -type f -exec rm -r "{}" \;',
        ]
    )

def task_tidy():
    '''
    clean submods and sota/lang repo
    '''
    yield dict(
        name='sota/lang',
        actions=['git clean -xfd'],
    )
    for submod in SUBS2SHAS.keys():
        yield dict(
            name=submod,
            actions=[
                fmt('cd {submod} && git reset --hard HEAD && git clean -xfd')
            ],
        )
