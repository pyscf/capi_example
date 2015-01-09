from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy

extra_info = {
    'include_dirs': [numpy.get_include()],
    'library_dirs': ['.'],
    'libraries': ['fenergy'],
    'extra_compile_args': ['-fopenmp','-ffast-math'],
    'extra_link_args': ['-fopenmp'],
    'language': 'c++',
}


ext_modules = [Extension('cythonenergy',
                         ['cythonenergy.pyx', 'cppenergy.cpp'],
                         **extra_info
                        )]

setup(
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules,
    script_args = ['build_ext', '--inplace']
)

# build .so with    python setup.py build_ext -i


