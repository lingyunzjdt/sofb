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

    fprintf(stderr, "new pos: %g %g op= %ld\n", x1, x2, op);

    switch(op) {
    case 0:
        fprintf(stderr, "NOTING is DONE for op=0\n");
        break;
    case 1: /* ABS: use bpm set 1 */
        /* save to set 1 */
        *(double*) pasub->vala = xrf1 + (x1c - x1);
        *(double*) pasub->valb = xrf2 + (x2c - x2);
        break;
    case 2: 
        break;
    default:
        fprintf(stderr, "Undefined code: %d\n", op);
    }
    return 0;
}

epicsRegisterFunction(sofbLocalBump);
