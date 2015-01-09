F77 = gfortran
FFLAGS = -fpic -g -shared

CC = gcc
CFLAGS = -fpic -g -shared

LD = gfortran
LDFLAGS = -shared

all: f2py ctypes cython

f2py: fortranenergy.so

fortranenergy.so : fortranenergy.F90
	$(F77) $(FFLAGS) -o libfenergy.so $^
	f2py -c fortranenergy.pyf -L. -lfenergy

ctypes: libcenergy.so

libcenergy.so: cenergy.c
	$(CC) $(CFLAGS) -o $@ $^

cython:
	python setup_cythonenergy.py

clean:
	/bin/rm *.o *.so
