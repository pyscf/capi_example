import numpy
import base
import ctypes

@base.timer
def energy(coord, charge):
    return nparray_pointer(coord, charge)
    #return call_by_symbol('run_', coord, charge)
    #return call_with_fpointer('euclid', coord, charge)
    #return call_with_callback(coord, charge)

def nparray_pointer(coord, charge):
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    fenergy = ctypes.CDLL('libfenergy.so')
    fenergy.run_.restype = ctypes.c_double
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += fenergy.run_(coord[i].ctypes.data_as(ctypes.c_void_p),
                              coord[j].ctypes.data_as(ctypes.c_void_p),
                              ctypes.byref(ctypes.c_double(charge[i])),
                              ctypes.byref(ctypes.c_double(charge[j])))
    return e

# fname is a string of the function name defined in C/Fortran
def call_by_symbol(fname, coord, charge):
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    fenergy = ctypes.CDLL('libfenergy.so')
    fn = getattr(fenergy, fname)
    fn.restype = ctypes.c_double
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += fn(coord[i].ctypes.data_as(ctypes.c_void_p),
                    coord[j].ctypes.data_as(ctypes.c_void_p),
                    ctypes.byref(ctypes.c_double(charge[i])),
                    ctypes.byref(ctypes.c_double(charge[j])))
    return e

# fdistname is a string of the function name defined in C/Fortran
def call_with_fpointer(fdistname, coord, charge):
    import _ctypes
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    cenergy = ctypes.CDLL('libcenergy.so')
    fn = getattr(cenergy, 'runcallback')
    fn.restype = ctypes.c_double
    fptr = ctypes.c_void_p(_ctypes.dlsym(cenergy._handle, fdistname))
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += fn(coord[i].ctypes.data_as(ctypes.c_void_p),
                    coord[j].ctypes.data_as(ctypes.c_void_p),
                    ctypes.c_double(charge[i]),
                    ctypes.c_double(charge[j]),
                    fptr)
    return e

def call_with_callback(coord, charge):
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    cenergy = ctypes.CDLL('libcenergy.so')
    fn = getattr(cenergy, 'runcallback')
    fn.restype = ctypes.c_double
    callbacktype = ctypes.CFUNCTYPE(ctypes.c_double,
                                    ctypes.POINTER(ctypes.c_double),
                                    ctypes.POINTER(ctypes.c_double))
# * returning a python object in callback function might have wrong
#   ref-counts. Store it in the external buffer to avoid the python object
#   being deleted.
# * the function prototype requires LP_c_double. It's not ctypes.c_double
#   object. The right return is the value of ctypes.c_double object.
    buf = numpy.empty(1)
    @callbacktype
    def mydist(r1, r2):
        r1 = numpy.ctypeslib.as_array(r1, (3,))
        r2 = numpy.ctypeslib.as_array(r2, (3,))
        rr = (r1 - r2)**2
        buf[0] = numpy.sqrt(rr.sum())
        return ctypes.c_double(buf[0]).value
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += fn(coord[i].ctypes.data_as(ctypes.c_void_p),
                    coord[j].ctypes.data_as(ctypes.c_void_p),
                    ctypes.c_double(charge[i]),
                    ctypes.c_double(charge[j]),
                    mydist)
    return e

if __name__ == '__main__':
    numpy.random.seed(1)
    n = 100
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge))


