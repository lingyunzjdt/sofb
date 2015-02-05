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
    double xrf11 = *(double*) pasub->c;
    double xrf12 = *(double*) pasub->d;
    double xrf21 = *(double*) pasub->e;
    double xrf22 = *(double*) pasub->f;
    double L = *(double*) pasub->g;
    double xfac = *(double*) pasub->h;
    long op = *(long*) pasub->i;
    double x2 = (offst + L * angle / 2.0) / xfac;
    double x1 = (offst - L * angle / 2.0) / xfac;

    fprintf(stderr, "new pos: %g %g op= %ld\n", x1, x2, op);

    double *px1, *px2;
    switch(op) {
    case 0:
        fprintf(stderr, "NOTING is DONE for op=0\n");
        break;
    case 1: /* ABS: use bpm set 1 */
        /* save to set 1 */
        *(double*) pasub->vala = x1;
        *(double*) pasub->valb = x2;
        break;
    case 3: /* REL: use bpm set 1 */
        *(double*) pasub->vala += x1;
        *(double*) pasub->valb += x2;                
        break;
    default:
        fprintf(stderr, "Undefined code: %d\n", op);
    }
    return 0;
}

epicsRegisterFunction(sofbLocalBump);
