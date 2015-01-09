double rsquare(double *dr);
double single_e(double chg1, double chg2, double rr);

double eval_o4(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *pt = coord + pt_id * 3;
        double *pcoord;
        double dr[3];
        double rr;
        double e = 0;

        for (ic = 0; ic < nc; ic++) {
                pcoord = coord + ic * 3;
                dr[0] = pcoord[0] - pt[0];
                dr[1] = pcoord[1] - pt[1];
                dr[2] = pcoord[2] - pt[2];
                rr = rsquare(dr);
                if (ic != pt_id) {
                        e += single_e(chg[pt_id], chg[ic], rr);
                }
        }
        return e;
}

