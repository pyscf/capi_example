import ctypes
import numpy
import base

# rewriting in C, can take the advantage of SSE3, to pipeline mul, add

@base.timer
def energy(coord, charge):
    coord = numpy.ascontiguousarray(coord)
    charge = numpy.ascontiguousarray(charge)
    libcoul = ctypes.CDLL('libcoul.so')
    nc = len(charge)
    qqr = numpy.empty((nc,nc))
    for i in range(nc):
        libcoul.eval_o3(ctypes.c_int(i), ctypes.c_int(nc),
                        coord.ctypes.data_as(ctypes.c_void_p),
                        charge.ctypes.data_as(ctypes.c_void_p),
                        qqr[i].ctypes.data_as(ctypes.c_void_p))
    e = qqr.sum() * .5
    return e

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

