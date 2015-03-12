#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<dbAccess.h>
#include<dbDefs.h>
#include<dbFldTypes.h>
#include<registryFunction.h>
#include<aSubRecord.h>
#include<waveformRecord.h>
#include<epicsExport.h>
#include<epicsTime.h>
#include<math.h>
#include<float.h>

static long sofbLocalBump(aSubRecord *pasub)
{
    double angle = *(double*) pasub->a;
    double offst = *(double*) pasub->b;
    double x1 = *(double*) pasub->c;
    double x2 = *(double*) pasub->d;
    double xrf1 = *(double*) pasub->e;
    double xrf2 = *(double*) pasub->f;
    double xfac = *(double*) pasub->g;
    double s1 = *(double*) pasub->h;
    double s2 = *(double*) pasub->i;
    double s3 = *(double*) pasub->j;
    long op = *(long*) pasub->k;

    double angle0 = (x2 - x1) / (s3 - s1) * xfac;
    double offst0 = x1*xfac + angle0 * (s2 - s1);

    /* calculated x1 and x2 */
    double x1c = (offst - angle * (s2 - s1)) / xfac;
    double x2c = (offst + angle * (s3 - s2)) / xfac;

    /* x = x0 - Href */
    /* keep x fixed at zero, Href changes same as required x0 */

    fprintf(stderr, "----------\n");
    fprintf(stderr, "input: angle= %g offset= %g xfac= %g, op= %ld\n", angle, offst, xfac, op);
    fprintf(stderr, "s: %g %g %g, op= %ld\n", s1, s2, s3, op);
    fprintf(stderr, "initial pos: %g %g op= %ld\n", x1, x2, op);
    fprintf(stderr, "initial ref: %g %g op= %ld\n", xrf1, xrf2, op);
    fprintf(stderr, "initial offset/angle: %g %g op= %ld\n", offst0, angle0, op);
    fprintf(stderr, "calculated pos: %g %g op= %ld\n", x1c, x2c, op);
    
    switch(op) {
    case 0:
        fprintf(stderr, "NOTING is DONE for op=0\n");
        break;
    case 1: /* ABS: use bpm set 1 */
        /* save to set 1 */
        /* *(double*) pasub->vala = xrf1 + (x1c - x1); */
        /* *(double*) pasub->valb = xrf2 + (x2c - x2); */
        /* *(double*) pasub->vala = x1c - x1; */
        /* *(double*) pasub->valb = x2c - x2; */
        *(double*) pasub->vala = x1c;
        *(double*) pasub->valb = x2c;
        break;
    case 2: 
        break;
    default:
        fprintf(stderr, "Undefined code: %d\n", op);
    }

    fprintf(stderr, "set H/V ref to : %g %g op= %ld\n",
            *(double*) pasub->vala,
            *(double*) pasub->valb,
            x1c, x2c, op);

    return 0;
}

int lower_bound_index(double s0, const double *sa, int sz)
{
    int i = 0, j = 0;
    for (i = 0; i < sz - 1; ++i) {
        if (s0 >= sa[i] && s0 < sa[i+1]) break;
    }
    return i;
}

int upper_bound_index(double s0, const double *sa, int sz)
{
    int i = 0, j = 0;
    for (i = 1; i < sz; ++i) {
        if (s0 > sa[i] && s0 < sa[i+1]) break;
    }
    return i;
}

static long setLocalBump(aSubRecord *pasub)
{
    const int NCOR = 2;
    int i, j, k, i0, i1;
    int ibpm[2];
    int icor[NCOR*2];
    double s0, s1;
    /* sbpm, scor increasing order */
    double *M = (double*) pasub->a;
    double *sbpm = (double*) pasub->b;
    double *scor = (double*) pasub->c;
    double sid = *(double*) pasub->d;
    fprintf(stderr, "BPMs %d: %f %f %f %f ...\n", pasub->nob,
            sbpm[0], sbpm[1], sbpm[2], sbpm[3]);
    /* s1-bpm, s2-ID, s3-bpm */
    ibpm[0] = lower_bound_index(sid, sbpm, pasub->nob);
    ibpm[1] = (ibpm[0]+1) % pasub->nob;
    fprintf(stderr, "BPM loc: %d %d\n", ibpm[0], ibpm[1]);
    
    s0 = sbpm[ibpm[0]];
    s1 = sbpm[ibpm[1]];
    i0 = lower_bound_index(s0, scor, pasub->noc);
    i1 = lower_bound_index(s1, scor, pasub->noc);
    if (i1 == i0) ++i1;
    for (j = 0; j < NCOR; ++j) {
        icor[NCOR-1-j] = (i0-j+pasub->noc) % pasub->noc;
        icor[NCOR+j] = (i1+j) % pasub->noc;
    }
    /* x = x0 - Href */
    /* keep x fixed at zero, Href changes same as required x0 */

    fprintf(stderr, "ID @ %f\n", sid);
    fprintf(stderr, "BPM: %f %f\n", sbpm[ibpm[0]], sbpm[ibpm[1]]);
    fprintf(stderr, "COR: %f %f %f %f\n", scor[icor[0]], scor[icor[1]],
            scor[icor[2]], scor[icor[3]]);
    
    return 0;
}

epicsRegisterFunction(sofbLocalBump);
epicsRegisterFunction(setLocalBump);
