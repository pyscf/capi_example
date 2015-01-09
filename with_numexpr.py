import numpy
import base
import numexpr

@base.timer
def energy(coord, charge):
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            ci = coord[i]
            cj = coord[j]
            dr = numexpr.evaluate('ci-cj')
            e += charge[i] * charge[j] / numpy.linalg.norm(dr)
    return e

if __name__ == '__main__':
    numpy.random.seed(1)
    n = 100
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge))

