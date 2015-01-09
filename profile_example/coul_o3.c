#include <math.h>

double rsquare(double *dr)
{
        return dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
}

double single_e(double chg1, double chg2, double rr)
{
        return chg1 * chg2 / sqrt(rr);
}

void eval_o3(int pt_id, int nc, double *coord, double *chg, double *rrinv)
{
        int ic;
        double *pt = coord + pt_id * 3;
        double *pcoord;
        double dr[3];
        double rr;

        for (ic = 0; ic < nc; ic++) {
                pcoord = coord + ic * 3;
                dr[0] = pcoord[0] - pt[0];
                dr[1] = pcoord[1] - pt[1];
                dr[2] = pcoord[2] - pt[2];
                rr = rsquare(dr);
                if (ic != pt_id) {
                        rrinv[ic] = single_e(chg[pt_id], chg[ic], rr);
                } else {
                        rrinv[pt_id] = 0;
                }
        }
}

