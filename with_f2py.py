import numpy
import base
import fortranenergy

# naive implementation of coulomb energy of N particle

@base.timer
def energy(coord, charge):
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += fortranenergy.run(coord[i], coord[j], charge[i], charge[j])
    return e

if __name__ == '__main__':
    numpy.random.seed(1)
    n = 100
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge))

