#include <math.h>
#include <pmmintrin.h>
#include <immintrin.h>

void eval_o2(int pt_id, int nc, double *coord, double *chg, double *rrinv)
{
        int ic;
        double *pt = coord + pt_id * 3;
        double *pcoord;
        double dr[3];
        double rr;
        double chg1 = chg[pt_id];

        for (ic = 0; ic < nc; ic++) {
                pcoord = coord + ic * 3;
                dr[0] = pcoord[0] - pt[0];
                dr[1] = pcoord[1] - pt[1];
                dr[2] = pcoord[2] - pt[2];
                rr = dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
                rrinv[ic] = chg1 * chg[ic] / sqrt(rr);
        }
        rrinv[pt_id] = 0;
}

double eval_o3(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *pt = coord + pt_id * 3;
        double *pcoord;
        double dr[3];
        double chg1 = chg[pt_id];
        double rr;
        double e = 0;

        for (ic = 0; ic < nc; ic++) {
                pcoord = coord + ic * 3;
                dr[0] = pcoord[0] - pt[0];
                dr[1] = pcoord[1] - pt[1];
                dr[2] = pcoord[2] - pt[2];
                rr = dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
                if (ic != pt_id) {
                        e += chg1 * chg[ic] / sqrt(rr);
                }
        }
        return e;
}

double eval_o4(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *coordx = coord;
        double *coordy = coord + nc;
        double *coordz = coord + nc*2;
        double ptx = coordx[pt_id];
        double pty = coordy[pt_id];
        double ptz = coordz[pt_id];
        double dr[3];
        double chg1 = chg[pt_id];
        double rr;
        double e = 0;

        for (ic = 0; ic < pt_id; ic++) {
                dr[0] = coordx[ic] - ptx;
                dr[1] = coordy[ic] - pty;
                dr[2] = coordz[ic] - ptz;
                rr = dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
                e += chg1 * chg[ic] / sqrt(rr);
        }
        return e;
}

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
                rr = dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
                e += chg[pt_id] * chg[ic] / sqrt(rr);
        }
        return e;
}

double eval_avx(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *coordx = coord;
        double *coordy = coord + nc;
        double *coordz = coord + nc*2;
        double e = 0;
        __m256d r0, r1, r2;
        __m256d ptx = _mm256_set1_pd(-coordx[pt_id]);
        __m256d pty = _mm256_set1_pd(-coordy[pt_id]);
        __m256d ptz = _mm256_set1_pd(-coordz[pt_id]);
        __m256d chg1 = _mm256_set1_pd(chg[pt_id]);
        __m256d e2 = _mm256_set1_pd(0);

        for (ic = 0; ic < pt_id-3; ic+=4) {
                r0 = _mm256_loadu_pd(coordx+ic);
                r0 = _mm256_add_pd(r0, ptx);
                r0 = _mm256_mul_pd(r0, r0);
                r1 = _mm256_loadu_pd(coordy+ic);
                r1 = _mm256_add_pd(r1, pty);
                r1 = _mm256_mul_pd(r1, r1);
                r0 = _mm256_add_pd(r0, r1);
                r2 = _mm256_loadu_pd(coordz+ic);
                r2 = _mm256_add_pd(r2, ptz);
                r2 = _mm256_mul_pd(r2, r2);
                r0 = _mm256_add_pd(r0, r2);
                r0 = _mm256_sqrt_pd(r0);
                r1 = _mm256_loadu_pd(chg+ic);
                r1 = _mm256_mul_pd(r1, chg1);
                r1 = _mm256_div_pd(r1, r0);
                e2 = _mm256_add_pd(e2, r1);
        }
        double e4[4];
        e2 = _mm256_hadd_pd(e2, e2);
        _mm256_storeu_pd(e4, e2);
        e = e4[0] + e4[2];
        double dr[3];
        double rr;
        for (; ic < pt_id; ic++) {
                dr[0] = coordx[ic] - coordx[pt_id];
                dr[1] = coordy[ic] - coordy[pt_id];
                dr[2] = coordz[ic] - coordz[pt_id];
                rr = dr[0] * dr[0] + dr[1] * dr[1] + dr[2] * dr[2];
                e += chg[pt_id] * chg[ic] / sqrt(rr);
        }
        return e;
}
