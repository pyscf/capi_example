import time

def timer(fn):
    def caller(*args):
        t0 = time.clock()
        w0 = time.time()
        res = fn(*args)
        print('CPU time = %8.2f, wall time = %8.2f' %
              (time.clock()-t0, time.time()-w0))
        return res
    return caller

