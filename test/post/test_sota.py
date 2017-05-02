#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys

from utils.shell import call

HELP = '''
usage:
    sota [options] [<source>]

options:
    -h --help     show this help
    --version     show version

source:
    text | file

sota is state of the art
'''

sys.dont_write_bytecode = True

def test_exists():
    assert os.path.exists('bin/sota')

def test_help():
    _, stdout, _ = call('./sota --help')
    assert HELP.strip() == stdout.strip()
