#include <math.h>
#include <pmmintrin.h>

double rsquare(double *dr);
double single_e(double chg1, double chg2, double rr);

// n**2*5 add, + n**2*4 mul, + n**2 sqrt, + n**2 div
// add 3 CPU cycles (cc)
// mul 5 cc
// sqrt ~ 20 cc
// div  ~ 20 cc

double eval_sse3(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *coordx = coord;
        double *coordy = coord + nc;
        double *coordz = coord + nc*2;
        double e = 0;
        __m128d r0, r1, r2;
        __m128d ptx = _mm_set1_pd(-coordx[pt_id]);
        __m128d pty = _mm_set1_pd(-coordy[pt_id]);
        __m128d ptz = _mm_set1_pd(-coordz[pt_id]);
        __m128d chg1 = _mm_set1_pd(chg[pt_id]);
        __m128d e2 = _mm_set1_pd(0);

        for (ic = 0; ic < pt_id-1; ic+=2) {
                r0 = _mm_loadu_pd(coordx+ic);
                r1 = _mm_loadu_pd(coordy+ic);
                r2 = _mm_loadu_pd(coordz+ic);
                r0 = _mm_add_pd(r0, ptx);
                r0 = _mm_mul_pd(r0, r0);
                r1 = _mm_add_pd(r1, pty);
                r1 = _mm_mul_pd(r1, r1);
                r0 = _mm_add_pd(r0, r1);
                r2 = _mm_add_pd(r2, ptz);
                r2 = _mm_mul_pd(r2, r2);
                r0 = _mm_add_pd(r0, r2);
                r0 = _mm_sqrt_pd(r0);
                r1 = _mm_loadu_pd(chg+ic);
                r1 = _mm_mul_pd(r1, chg1);
                r1 = _mm_div_pd(r1, r0);
                e2 = _mm_add_pd(e2, r1);
        }
        e2 = _mm_hadd_pd(e2, e2);
        double dr[3];
        _mm_store_sd(&e, e2);
        if (ic < pt_id) {
                double rr;
                dr[0] = coordx[ic] - coordx[pt_id];
                dr[1] = coordy[ic] - coordy[pt_id];
                dr[2] = coordz[ic] - coordz[pt_id];
                rr = rsquare(dr);
                e += single_e(chg[pt_id], chg[ic], rr);
        }
        return e;
}


