double rsquare(double *dr);
double single_e(double chg1, double chg2, double rr);

double eval_o5(int pt_id, int nc, double *coord, double *chg)
{
        int ic;
        double *coordx = coord;
        double *coordy = coord + nc;
        double *coordz = coord + nc*2;
        double ptx = coordx[pt_id];
        double pty = coordy[pt_id];
        double ptz = coordz[pt_id];
        double dr[3];
        double rr;
        double e = 0;

        for (ic = 0; ic < pt_id; ic++) {
                dr[0] = coordx[ic] - ptx;
                dr[1] = coordy[ic] - pty;
                dr[2] = coordz[ic] - ptz;
                rr = rsquare(dr);
                e += single_e(chg[pt_id], chg[ic], rr);
        }
        return e;
}
