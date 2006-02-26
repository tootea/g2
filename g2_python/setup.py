#!/usr/bin/env python
# On Unix, as root, install with : ./setup.py install
#    The result will generally be : /usr/lib/python2.4/site-packages/g2.so
# On Windows, install with : setup.py install
#    The result will generally be : C:\Python24\lib\site-packages\g2.pyd
# Then in Python say : import g2

# For a module based on libg2.so, make sure libg2.so is in the link path
# (you may have to add a link like libg2.so -> libg2.so.0.0.70).
# For a stand alone module (not recommended), make sure libg2.a is in
# the link path (very likely, given -L../), and libg2.so is not.
# Alternatively, add '-static' to link_args below.

from distutils.core import setup, Extension

import sys
import platform

build_ext_opts = { 'build_temp' : '.', 'build_lib' : '.' }

# called without arguments, just build the module in directory g2_python
if len(sys.argv) == 1:
    build_ext_opts['force'] = True
    sys.argv.append('build_ext')

try:
    f = file('../config.status')
except IOError:
    print 'ERROR : cannot read config.status'
    link_args = []
    compile_args = []
else :
    s = f.read()
    f.close()

    j = i = s.find('@LDFLAGS@') + 10
    while s[j] != '%': j += 1
    link_args = s[i:j].split()

    j = i = s.find('@DEFS@') + 7
    while s[j] != '%': j += 1
    compile_args = s[i:j].split()

# on Linux, strip debugging info from lib
if platform.system() == 'Linux':
    link_args += ['-s']

if platform.python_compiler()[0:3] == 'GCC' and 'sparc' in platform.machine():
    link_args += ['-fPIC', '-Wl,-O2', '-Wl,-Map=g2.map']

g2base = Extension( 'g2',
                    sources = ['g2module.c'],
                    include_dirs = ['../src'],
                    library_dirs = ['../'],
                    libraries = ['g2'],
                    extra_compile_args = compile_args,
                    extra_link_args = link_args)

setup( name = 'PythonG2',
       author = 'Tijs Michels',
       author_email = 'tijs@users.sourceforge.net',
       url = 'http://g2.sourceforge.net/',
       license = 'GNU Lesser General Public License, version 2.1 or above',
       version = '0.1',
       description = 'Easy to use, portable yet powerful 2D graphics library',
       ext_modules = [g2base],
       options = { 'build_ext' : build_ext_opts })
