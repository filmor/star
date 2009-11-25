from os.path import join, basename
from glob import glob
import sys

VERSION='0.0'
APPNAME='star'

srcdir = 'src'

program_file = 'main.cpp'

sources = [basename(i) for i in glob(join(srcdir, '*.cpp'))]

blddir = 'build'

include_dir = 'include'

def set_options(opt):
    opt.tool_options('compiler_cxx')
    opt.tool_options('boost')

def configure(conf):
    for i in '-O3 -Wall -g3 -fomit-frame-pointer -march=prescott'.split():
        conf.env.append_value('CXXFLAGS', i)

    conf.check_tool('compiler_cxx')
    conf.check_tool('boost')

    # GLFW
    # Darwin has proper support now
    conf.check_cxx(lib='glfw', uselib_store='GLFW')
    if sys.platform == 'darwin':
        conf.env['LINKFLAGS_GLFW'] = '-framework Carbon -framework AGL ' \
                                   + '-framework OpenGL'
    elif sys.platform == 'linux2':
        conf.check_cxx(lib='GL', uselib_store='GLFW')
        conf.check_cxx(lib='GLU', uselib_store='GLFW')

    # GD
    conf.check_cxx(lib='gd', uselib_store='GD')

    # Lua
    conf.check_cfg(package='lua', args='--cflags --libs', uselib_store='LUA')

    # FMOD
    conf.check_cxx(lib='fmodex', uselib_store='FMOD')

    conf.check_boost(lib='system thread filesystem', min_version='1.35',
            uselib_store='BOOST')

def build(bld):
    bld.add_subdirs('src')

