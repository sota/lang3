#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os

def test_exists():
    assert os.path.exists('bin/sota')
