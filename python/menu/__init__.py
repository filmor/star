# Copyright 2004-2005 Joe Wreschnig, Michael Urman
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation
#
# $Id: __init__.py 3236 2006-05-07 18:34:42Z piman $

import sys
import traceback

from glob import glob
from os.path import dirname, basename, join

base = dirname(__file__)
self = basename(base)
modules = [f[:-3] for f in glob(join(base, "[!_]*.py"))]
modules = ["%s.%s" % (self, basename(m)) for m in modules]

for i, name in enumerate(modules):
    try: menu = __import__(name, {}, {}, self)
    except Exception, err:
        traceback.print_exc()
        continue
    menu = __import__(name, {}, {}, self)
    modules[i] = (format.extensions and name.split(".")[1])

modules = filter(None, modules)
modules.sort()

def filter(filename):
    for ext in _infos.keys():
        if filename.lower().endswith(ext): return True
    return False

_dict["Quit"] = lambda : sys.exit (0)

def show ():
    Menu(_dict).show ()

del base, self, modules
