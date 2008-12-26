from os.path import join, basename
from glob import glob
import sys

VERSION='0.0'
APPNAME='star'

srcdir = 'src'

program_file = 'main.cpp'

sources = [basename(i) for i in glob(join(srcdir, '*.cpp'))]
sources.remove(program_file)

blddir = 'build'

include_dir = 'include'

def set_options(opt):
    opt.add_option('--with-fmod-prefix', type='string', dest='fmod_prefix')
    opt.tool_options('compiler_cxx')
    opt.tool_options('boost')

def configure(conf):
    for i in '-O3 -Wall -g3 -fomit-frame-pointer -march=prescott'.split():
        conf.env.append_value('CXXFLAGS', i)

    conf.check_tool('compiler_cxx')
    conf.check_tool('boost')

    # GLFW
    if sys.platform == 'darwin':
        conf.env['LINKFLAGS_GLFW'] = '-framework Carbon -framework AGL ' \
                                   + '-framework OpenGL'
        conf.env['LIB_GLFW'] = 'glfw'

    # GD
    conf.check_cxx(lib='gd', uselib_store='GD')

    # Luabind
    conf.check_cfg(package='lua', args='--cflags --libs', uselib_store='LUA')
    conf.check_cxx(lib='luabind', uselib_store='LUABIND')

    # FMOD
    conf.env['LIBPATH_FMOD'] = '/usr/local/lib'
    conf.env['CPPPATH_FMOD'] = '/usr/local/include'
    conf.check_cxx(lib='fmodex', uselib_store='FMOD')

    conf.check_boost(lib='system thread filesystem', min_version='1.35',
            uselib_store='BOOST')


def build(bld):
    task = bld.new_task_gen()
    task.features = 'cxx cprogram'
    task.source = sources + [program_file]
    task.target=APPNAME
    task.includes = '../include'
    task.uselib = "GLFW GD BOOST_SYSTEM BOOST_THREAD BOOST_FILESYSTEM LUA " \
                + "LUABIND FMOD"


