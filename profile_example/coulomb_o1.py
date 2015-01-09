import numpy
import base

# Using numpy functions is much more efficient than loop in python

#@base.timer
def energy(coord, charge):
    nc = len(charge)
    xx = coord[:,0].reshape(nc,1) - coord[:,0]
    yy = coord[:,1].reshape(nc,1) - coord[:,1]
    zz = coord[:,2].reshape(nc,1) - coord[:,2]
    r = xx**2 + yy**2 + zz**2
    r[numpy.diag_indices(nc)] = 1e-60
    r = numpy.sqrt(r)
    qq = charge[:,None] * charge[None,:]
    qq[numpy.diag_indices(nc)] = 0
    e = (qq/r).sum() * .5
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

