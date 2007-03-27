# -*- encoding:utf8 -*-

import glob
from os.path import join

name = "star"
sources = glob.glob('src/*.cpp')
tests = glob.glob('test/*.cpp')
prefix = "/Users/bs/Gentoo/usr"
fmod_prefix = "/Developer/FMOD Programmers API/api"
libdir = [ join(prefix, "lib"), join(fmod_prefix, "lib") ]
include = [ "include", join(prefix, "include"), join(fmod_prefix, "inc") ]
libs = "boost_filesystem-mt-s fmodex".split()
cxxflags = "-O3 -fomit-frame-pointer -march=prescott -g3"

env = Environment(CXXFLAGS=cxxflags, CPPPATH=include, LIBPATH=libdir, LIBS=libs)

objects = [ env.Object(i) for i in sources ]

if ARGUMENTS.get('test', 0):
    for i in tests:
        env.Program([i] + objects)
else:
    env.Program(name, objects)

