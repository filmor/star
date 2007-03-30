# -*- encoding:utf8 -*-

import glob
from os.path import join

name = "star"
sources = glob.glob('src/*.cpp')
tests = glob.glob('test/*.cpp')
prefix = "/Users/bs/Gentoo/usr"
libdir = [ join(prefix, "lib") ]
include = [ "include", join(prefix, "include") ]
libs = "boost_thread boost_filesystem fmodex".split()
cxxflags = "-O3 -fomit-frame-pointer -march=prescott "
debugflags = "-march=prescott -g3"

if ARGUMENTS.get('debug', 0):
    cxxflags = debugflags

env = Environment(CXXFLAGS=cxxflags, CPPPATH=include, LIBPATH=libdir, LIBS=libs)

objects = [ env.Object(i) for i in sources ]

if ARGUMENTS.get('test', 0):
    for i in tests:
        env.Program([i] + objects)
else:
    env.Program(name, objects)

