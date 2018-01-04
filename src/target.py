#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys
import cli

from sota.lexer import Lexer

def entry_point(argv):
    args = cli.parse(argv)
    if '<source>' in args:
        source = args['<source>']
        lexer = Lexer()
        if os.path.exists(source):
            with open(source, 'r') as f:
                source = f.read()
        print('source found:')
        print(source)
        tokens = lexer.scan(source)
        for token in tokens:
            print(token.to_str())
    else:
        print('repl time')
    return 0

def target(*args):
    return entry_point, None

if __name__ == '__main__':
    exitcode = entry_point(sys.argv)
    sys.exit(exitcode)
