Cython
======

* pyx
  - in the head
```python
#cython: boundscheck=False
#cython: wraparound=False
#cython: overflowcheck.fold=False
```
  - memoryview vs numpy.ndarray

* compiling. see example setup_cythonenergy.py

* c++ binding
  - for pyx
    cimport libcpp
    vector[T]
  - setup.py
    Extension(language='c++')

* interface layer for external libraries


ctypes
======

* passing pointer (with numpy array)
  ctypes.byref
  numpy.ndarray.ctypes.data_as(ctypes.POINTER(ctypes.c_double))

* call by symbol

* passing function pointer
  - callback function

* defined struct
```python
class RGB(ctypes.Structure):
    _field_ = [('r', ctypes.c_int),
               ('g', ctypes.c_int),
               ('b', ctypes.c_int),]
```

cons
1. calling overhead 
2. python object lifetime. Two examples of memory leak
  - nparray.copy().ctypes
  - def f(alist): return numpy.array(alist).ctypes
3. nparray data contiguous
  - use function numpy.ascontiguousarray
4. str in python3 is unicode string object. A python single char string
  cannot be used with ctypes.c_char. see
  https://docs.python.org/2/library/ctypes.html
5. The dynamic loader may mess up the libraries if two dynamic libraries have
  the same name and one was already loaded in memory


f2py
====

F2py is a tool of numpy.

* callback function

others
======
* Swig
* numba (llvm required)
* weave (out of date, but can be an example of python-cpp interface code)

