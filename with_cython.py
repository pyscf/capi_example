import numpy
import base
#import pyximport
#pyximport.install(setup_args={'include_dirs': [numpy.get_include()]})
import cythonenergy

# naive implementation of coulomb energy of N particle

@base.timer
def energy(coord, charge):
    #return cythonenergy.energy_naive(coord, charge)
    return cythonenergy.energy_fast(coord, charge)
    #return cythonenergy.energy_f(coord, charge)
    #return cythonenergy.energy_cpp(coord, charge)

if __name__ == '__main__':
    numpy.random.seed(1)
    n = 100
    charge = numpy.random.random(n)
    coord = numpy.random.random((n,3))
    print(energy(coord, charge))


