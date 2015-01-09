python profiler
===============

ipython notebook
----------------
run

        ipython notebook coulomb_energy.ipynb

to profile in ipython IDE.


cProfile
--------
profile python function call

save profiler log to output file
 
        python -m cProfile -o coulomb_o0.prof coulomb_o0.py
 
print profiler log

        python -c "import pstats; pstats.Stats('coulomb_o0.prof').print_stats()"

or 

        python -c "import pstats; pstats.Stats('coulomb_o0.prof').sort_stats('cum').print_stats()"

line_profiler
-------------
decorate the target funtion with `@profile`

```python
@profile
def energy(coord, charge):
    ...
```

then run

        kernprof.py -l -v coulomb_o0.py

memory_profiler
---------------
decorate the target funtion with `@profile`, then

python -m memory_profiler coulomb_o0.py



C profiler
==========

valgrind
--------
        valgrind --tool=callgrind --simulate-cache=yes
        kcachegrind


perf
----
on ubuntu,

        sudo apt-get install linux-tools

to install perf.  Run perf 

        perf stat python coulomb_o3.py
        perf record -f python coulomb_o3.py
        perf report


oprofile, operf
---------------
on ubuntu,

        sudo apt-get install oprofile

run operf

        operf python coulomb_o3.py
        opreport -l -a

others
------
* vtune
* gprof


