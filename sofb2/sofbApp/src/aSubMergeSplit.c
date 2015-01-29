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

#define MERGE_INP(pval, dblk, val, sz)                  \
    if (dblk.type == CONSTANT) goto stats;              \
    memcpy(pval, val, sz * sizeof(double));             \
    pval += sz

static long mergePvs(aSubRecord *pasub)
{
    // output: waveform, avg, rms, min, max, std, var
    double *pval = (double *)pasub->vala;
    int i = 0;
    double s1 = 0.0;
    double s2 = 0.0;
    double xmin = DBL_MAX;
    double xmax = DBL_MIN;
    double xstd = 0.0, xvar = 0.0, xrms = 0.0;
    /*
    if (pasub->inpa.type == CONSTANT) goto finish;
    memcpy(pval, pasub->a, pasub->noa * sizeof(double));
    pval += pasub->noa;
    */
    MERGE_INP(pval, pasub->inpa, pasub->a, pasub->noa);
    MERGE_INP(pval, pasub->inpb, pasub->b, pasub->nob);
    MERGE_INP(pval, pasub->inpc, pasub->c, pasub->noc);
    MERGE_INP(pval, pasub->inpd, pasub->d, pasub->nod);
    MERGE_INP(pval, pasub->inpe, pasub->e, pasub->noe);
    MERGE_INP(pval, pasub->inpf, pasub->f, pasub->nof);
    MERGE_INP(pval, pasub->inpg, pasub->g, pasub->nog);
    MERGE_INP(pval, pasub->inph, pasub->h, pasub->noh);
    MERGE_INP(pval, pasub->inpi, pasub->i, pasub->noi);
    MERGE_INP(pval, pasub->inpj, pasub->j, pasub->noj);
    MERGE_INP(pval, pasub->inpk, pasub->k, pasub->nok);
    MERGE_INP(pval, pasub->inpl, pasub->l, pasub->nol);
    MERGE_INP(pval, pasub->inpm, pasub->m, pasub->nom);
    MERGE_INP(pval, pasub->inpn, pasub->n, pasub->non);
    MERGE_INP(pval, pasub->inpo, pasub->o, pasub->noo);
    MERGE_INP(pval, pasub->inpp, pasub->p, pasub->nop);
    MERGE_INP(pval, pasub->inpq, pasub->q, pasub->noq);
    MERGE_INP(pval, pasub->inpr, pasub->r, pasub->nor);
    MERGE_INP(pval, pasub->inps, pasub->s, pasub->nos);
    MERGE_INP(pval, pasub->inpt, pasub->t, pasub->not);
    MERGE_INP(pval, pasub->inpu, pasub->u, pasub->nou);

stats:
    pval = (double*) pasub->vala;
    for (i = 0; i < pasub->nova; ++i) {
        s1 += pval[i];
        s2 += pval[i] * pval[i];
        if (pval[i] < xmin) xmin = pval[i];
        if (pval[i] > xmax) xmax = pval[i];
    }
    s2 /= pasub->nova;
    s1 /= pasub->nova;
    xrms = sqrt(s2);
    xvar = s2 - s1 * s1;
    xstd = sqrt(xvar);
    /* avg, rms, min, max, std, var */
    if (pasub->outb.type == CONSTANT) goto finish;
    memcpy(pasub->valb, &s1, sizeof(double));
    if (pasub->outc.type == CONSTANT) goto finish;
    memcpy(pasub->valc, &xrms, sizeof(double));
    if (pasub->outd.type == CONSTANT) goto finish;
    memcpy(pasub->vald, &xmin, sizeof(double));
    if (pasub->oute.type == CONSTANT) goto finish;
    memcpy(pasub->vale, &xmax, sizeof(double));
    if (pasub->outf.type == CONSTANT) goto finish;
    memcpy(pasub->valf, &xstd, sizeof(double));
    if (pasub->outg.type == CONSTANT) goto finish;
    memcpy(pasub->valg, &xvar, sizeof(double));

finish:
    return 0;
}

epicsRegisterFunction(mergePvs);
