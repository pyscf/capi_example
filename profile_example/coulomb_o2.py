import numpy
import base

# computing xx, yy, zz, then rr takes > 50% time, numpy.dot (dgemm) is more
# efficient

#@base.timer
def energy(coord, charge):
    rr = numpy.dot(coord, coord.T)
    rd = rr.diagonal()
    rr = rd[:,None] + rd - rr*2
    rr[numpy.diag_indices_from(rr)] = 1e-60
    r = numpy.sqrt(rr)
    qq = charge[:,None] * charge[None,:]
    qq[numpy.diag_indices_from(rr)] = 0
    e = (qq/r).sum() * .5
    return e

# aggresive optimzation, that's the best we can do in pure python

@base.timer
def energy1(coord, charge):
    rr = numpy.dot(coord*2, coord.T)
    rd = rr.diagonal() * .5
    rd2 = rd[:,None] + rd
    rd2 -= rr
    rr = rd2
    rr[numpy.diag_indices_from(rr)] = 1e300
    r = 1/numpy.sqrt(rr)
    e = reduce(numpy.dot, (charge, r, charge)) * .5
    return e

# or use numexpr

@base.timer
def energy2(coord, charge):
    import numexpr
    rr = numpy.dot(coord, coord.T)
    rd = rr.diagonal()
    rd1 = rd[:,None]
    rr = numexpr.evaluate('rd1 + rd - rr*2')
    rr[numpy.diag_indices_from(rr)] = 1e300
    r = 1/numpy.sqrt(rr)
    e = reduce(numpy.dot, (charge, r, charge)) * .5
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
    print(energy2(coord, charge))

