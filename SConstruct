# -*- encoding:utf8 -*-

from os.path import join as Join

name = "star"
sources = Glob('src/*.cpp')
tests = Glob('test/*.cpp')
prefix = "/Users/bs/Gentoo/usr"
libdir = [ Join(prefix, "lib") ]
include = [ "include", Join(prefix, "include") ]
libs = "gd glfw boost_system boost_thread boost_filesystem lua fmodex luabind".split()
cxxflags = "-O3 -Wall -g3 -fomit-frame-pointer -march=prescott"# -D_GLIBCXX_CONCEPT_CHECKS"

ldflags = "-Wl,-search_paths_first,-bind_at_load -bind_at_load".split()
ldflags += "-framework Carbon -framework AGL -framework OpenGL".split()

env = Environment(CXXFLAGS=cxxflags, CPPPATH=include, LIBPATH=libdir, LIBS=libs, LINKFLAGS = ldflags)

objects = [ env.Object(i) for i in sources if i != "src/main.cpp" ]

# if ARGUMENTS.get('test', 0):
if 'test' in COMMAND_LINE_TARGETS:
    for i in tests:
        env.Program([i] + objects)
else:
    env.Program(name, objects)

