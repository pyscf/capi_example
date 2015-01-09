import ctypes
import numpy
import base

# ctypes causes large calling overhead

@base.timer
def energy(coord, charge):
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    libcoul = ctypes.CDLL('libcoul.so')
    libcoul.eval_o4.restype = ctypes.c_double
    nc = len(charge)
    c_nc = ctypes.c_int(nc)
    c_coord = coord.ctypes.data_as(ctypes.c_void_p)
    c_charge = charge.ctypes.data_as(ctypes.c_void_p)
    e = 0
    for i in range(nc):
        e += libcoul.eval_o4(ctypes.c_int(i),
                             c_nc,
                             c_coord,
                             c_charge)
    return e * .5

if __name__ == '__main__':
    import coulomb_o0
    numpy.random.seed(1)
    n = 100
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge) - coulomb_o0.energy(coord, charge))

    n = 4000
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge))

