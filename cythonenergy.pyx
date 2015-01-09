#cython: boundscheck=False
#cython: wraparound=False
#cython: overflowcheck.fold=False
#cython: cdivision=True
import numpy
cimport numpy
cimport cython
cimport libc.math
import fortranenergy
from libcpp.vector cimport vector

         
cdef extern double run_(double *coord1, double *coord2,
                        double *charge1, double *charge2)

cdef extern from 'cppenergy.h' namespace 'coulomb':
    double runcpp(vector[double]& ri, vector[double]& rj,
                  double chg1, double chg2)

def energy_naive(numpy.ndarray[double,ndim=2] coord, numpy.ndarray[double] charge):
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            dr = coord[i] - coord[j]
            e += charge[i] * charge[j] / numpy.linalg.norm(dr)
    return e

def energy_fast(double[:,:] coord, double[:] charge):
    cdef int i
    cdef int j
    cdef int nc = len(charge)
    cdef double e = 0
    cdef double dx, dy, dz
    for i in range(nc):
        for j in range(i):
            dx = coord[i,0] - coord[j,0]
            dy = coord[i,1] - coord[j,1]
            dz = coord[i,2] - coord[j,2]
            r = libc.math.sqrt(dx*dx+dy*dy+dz*dz)
            e += charge[i] * charge[j] / r
    return e

def energy_f(numpy.ndarray[double,ndim=2] coord, numpy.ndarray[double] charge):
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += run_(&coord[i,0], &coord[j,0], &charge[i], &charge[j])
    return e

def energy_cpp(numpy.ndarray[double,ndim=2] coord, numpy.ndarray[double] charge):
    nc = len(charge)
    e = 0
    for i in range(nc):
        for j in range(i):
            e += runcpp(coord[i], coord[j], charge[i], charge[j])
    return e
