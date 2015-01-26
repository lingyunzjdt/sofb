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

#define MERGE_INP(pval, dblk, val, sz)                  \
    if (dblk.type == CONSTANT) goto finish;             \
    memcpy(pval, val, sz * sizeof(float));              \
    pval += sz

static long mergePvs(aSubRecord *pasub)
{
    float *pval = (float *)pasub->vala;
    int i = 0;
    float sum = 0.0;
    float sum2 = 0.0;
    /*
    if (pasub->inpa.type == CONSTANT) goto finish;
    memcpy(pval, pasub->a, pasub->noa * sizeof(float));
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

finish:
    pval = (float*) pasub->vala;
    for (i = 0; i < pasub->nova; ++i) {
        sum += pval[i];
        sum2 += pval[i] * pval[i];
    }
    if (pasub->outb.type != CONSTANT) memcpy(pasub->valb, &sum, sizeof(float));
    if (pasub->outc.type != CONSTANT) memcpy(pasub->valc, &sum2, sizeof(float));

    return 0;
}

epicsRegisterFunction(mergePvs);
