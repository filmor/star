# -*- encoding:utf8 -*-

import glob
from os.path import join

name = "star"
sources = glob.glob('src/*.cpp')
tests = glob.glob('test/*.cpp')
prefix = "/Users/bs/Gentoo/usr"
libdir = [ join(prefix, "lib") ]
include = [ "include", join(prefix, "include"), join(prefix, "include/python2.5") ]
libs = "boost_thread boost_filesystem boost_python fmodex".split()
frameworks = "Python".split()
cxxflags = "-O3 -Wall -g3 -fomit-frame-pointer -march=prescott -D_GLIBCXX_CONCEPT_CHECKS"

ldflags = []
for i in frameworks:
    ldflags += ["-framework"]
    ldflags += [i]

env = Environment(CXXFLAGS=cxxflags, CPPPATH=include, LIBPATH=libdir, LIBS=libs, LINKFLAGS = ldflags)

objects = [ env.Object(i) for i in sources if i != "src/main.cpp" ]

# if ARGUMENTS.get('test', 0):
if 'test' in COMMAND_LINE_TARGETS:
    for i in tests:
        env.Program([i] + objects)
else:
    env.Program(name, objects + ['src/main.cpp'])

