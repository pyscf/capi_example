#include <math.h>

double euclid(double *ri, double *rj)
{
        double dx = ri[0] - rj[0];
        double dy = ri[1] - rj[1];
        double dz = ri[2] - rj[2];
        return sqrt(dx*dx + dy*dy*dy*dy + dz*dz);
}

double runcallback(double *ri, double *rj, double chg1, double chg2,
                   double (*fdistance)())
{
        return chg1 * chg2 / fdistance(ri, rj);
}

