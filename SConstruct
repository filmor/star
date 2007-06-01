# -*- encoding:utf8 -*-

import glob
from os.path import join

name = "star"
sources = glob.glob('src/*.cpp')
tests = glob.glob('test/*.cpp')
prefix = "/usr"
libdir = [ join(prefix, "lib"), join(prefix, "lib/python2.4/config") ]
include = [ "include", join(prefix, "include"), join(prefix, "include/python2.4") ]
libs = "boost_thread boost_filesystem boost_python fmodex64 python2.4".split()
cxxflags = "-O3 -Wall -g3 -fomit-frame-pointer -march=k8 -D_GLIBCXX_CONCEPT_CHECKS"

ldflags = []

env = Environment(CXXFLAGS=cxxflags, CPPPATH=include, LIBPATH=libdir, LIBS=libs, LINKFLAGS = ldflags)

objects = [ env.Object(i) for i in sources if i != "src/main.cpp" ]

# if ARGUMENTS.get('test', 0):
if 'test' in COMMAND_LINE_TARGETS:
    for i in tests:
        env.Program([i] + objects)
else:
    env.Program(name, objects + ['src/main.cpp'])

