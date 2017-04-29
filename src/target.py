#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import cli

def entry_point(argv):
    args = cli.parse(argv)
    return 0

def target(*args):
    return entry_point
