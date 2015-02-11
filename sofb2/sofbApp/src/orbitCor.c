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

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#define DEBUG

static long solveSVD(aSubRecord *pasub)
{
    int i, j, k, k1, k2;
    double *buf = NULL;
    /* A = U*S*V^T */
    /* a: full matrix */
    double *pA = (double *)pasub->a;
    /* b: active/inactive X/Y BPM */
    char *bsel = (int *)pasub->b;
    /* c: active/inactive X/Y Cor */
    char *csel = (int *)pasub->c;
    /* d: keep n sv */
    int sn = *(long*)pasub->d;
    /* f: weight of BPMS */
    double *pw = (double*)pasub->f;
    
    /* output: */
    /* a,b,c: M, Minv, S */
    /* int m = pasub->nob + pasub->noc; */
    int m = 0, n = 0;
    for (j = 0; j < pasub->noc; ++j) n += csel[j];
    double *pM = (double*) pasub->vala;
    pasub->neva = 0;
    k1 = k2 = 0;
    for (i = 0; i < pasub->nob; ++i) {
        /* skip some BPMs */
        if (!bsel[i]) continue;
        ++m;
        for (j = 0; j < pasub->noc; ++j) {
            /* skip some correctors */
            if (!csel[j]) continue;
            k2 = i * (pasub->noc) + j;
            pM[k1++] = pA[k2] * pw[i]; /* with weight */
            ++(pasub->neva);
        }
    }
    /* output d, e: nbpm, ncor */
    *(long *)pasub->vald = m;
    *(long *)pasub->vale = n;

 #ifdef DEBUG
    fprintf(stderr, "M size: %d %d\n", m, n);
    for(i = 0; i < pasub->nof; ++i) fprintf(stderr, " %g", pw[i]);
    fprintf(stderr, "\n");
 #endif
    
    if (m == 0 || n == 0)  {
     #ifdef DEBUG
        fprintf(stderr, "No BPM (%d) or COR (%d) are selected, quit\n", m, n);
     #endif
        
        return 0;
    }
    
    int nrow = m > n ? m : n;
    int ncol = n < m ? n : m;
    gsl_matrix_view Av = gsl_matrix_view_array(pM, m, n);
    gsl_matrix *A = gsl_matrix_alloc(nrow, ncol);
    if (m < n) {
        gsl_matrix_transpose_memcpy(A, &(Av.matrix));
    } else {
        gsl_matrix_memcpy(A, &(Av.matrix));
    }
    gsl_matrix *V = gsl_matrix_alloc(A->size2, A->size2);
    gsl_vector *S = gsl_vector_alloc(A->size2);
    /* SVD(A), where A is (m,n) and m >= n */
    /* gsl_linalg_SV_decomp_jacobi (&(Av.matrix), V, S); */
    gsl_linalg_SV_decomp_jacobi (A, V, S);

    /* output c: S */
    double *pS = (double*)pasub->valc;
    double *pSfull = (double*) pasub->vali;
    /* double *pSlog = (double*) pasub->valj; */
    /* double *pSflog = (double*) pasub->valk; */
    for(i = 0; i < pasub->novc; ++i) {
        pSfull[i] = i < S->size ? gsl_vector_get(S, i) : 0.0;
        pS[i] = (i < S->size && i < sn) ? gsl_vector_get(S, i) : 0.0;
        /* pSlog[i]  = pS[i] > 0.0 ? log(pS[i]) : 0.0; */
        /* pSflog[i] = pSfull[i] > 0.0 ? log(pSfull[i]) : 0.0; */
    }
    pasub->nevi = S->size < pasub->novi ? S->size : pasub->novi; 
    pasub->nevc = sn < pasub->nevi ? sn : pasub->nevi;

    /* set U and V */
    buf = (double*) pasub->valf;
    for (i = 0; i < A->size1; ++i) {
        for (j = 0; j < A->size2; ++j) {
            buf[i*A->size2+j] = gsl_matrix_get(A, i, j);
        }
    }

    buf = (double*) pasub->valg;
    for (i = 0; i < V->size1; ++i) {
        for (j = 0; j < V->size2; ++j) {
            buf[i*V->size2+j] = gsl_matrix_get(V, i, j);
        }
    }

    double *tmp = (double*) malloc(pasub->noa * sizeof(double));

    /* double check U*S */
    for (i = 0; i < A->size1; ++i) {
        for (j = 0; j < S->size; ++j) {
            double s = 0.0;
            /* for (k = 0; k < S->size; ++k)
               s += gsl_matrix_get(A, i, k) * gsl_vector_get(S, k, j); */
            s = gsl_matrix_get(A, i, j) * gsl_vector_get(S, j);
            tmp[i*S->size + j] = s;
        }
    }
    buf = (double*) pasub->valh;
    for (i = 0; i < A->size1; ++i) {
        for (j = 0; j < A->size2; ++j) {
            double s = 0.0;
            for (k = 0; k < A->size2; ++k)
                s += tmp[i*A->size2 + k] * gsl_matrix_get(V, j, k);
            buf[i*S->size + j] = s;
        }
    }
    
    double *pMinv = (double*) pasub->valb;
    /* A^{-1} = V S^{-1} U^T */
    /* no transpose */
    for (i = 0; i < A->size2; ++i) {
        for (j = 0; j < A->size2; ++j) {
            double s = 0.0;
            /*
              for (k = 0; k < A->size2; ++k) {
              s += gsl_matrix_get(V, i, k) * gsl_matrix_get(S, k, j);
              } 
            */
            /* s = gsl_matrix_get(V, i, j) / gsl_vector_get(S, j); */
            s = j < sn ? gsl_matrix_get(V, i, j) / gsl_vector_get(S, j) : 0.0;
            tmp[i*A->size2 + j] = s;
        }
    }
    for (i = 0; i < A->size2; ++i) {
        for (j = 0; j < A->size1; ++j) {
            double s = 0.0;
            for (k = 0; k < A->size2; ++k) {
                s += tmp[i*A->size2+k] * gsl_matrix_get(A, j, k);
            } 
            pMinv[i*A->size1 + j] = s;
        }
    }
    pasub->nevb = A->size2 * A->size1;
    fprintf(stderr, "Minv size: %d %d (%d)\n", A->size2, A->size1, pasub->nevb);
    
    free(tmp);

    /* set bsel and csel */
    pasub->novj = pasub->nob;
    for (i = 0; i < pasub->nob; ++i) ((char*)pasub->valj)[i] = bsel[i];
    pasub->novk = pasub->noc;
    for (i = 0; i < pasub->noc; ++i) ((char*)pasub->valk)[i] = csel[i];
    for (buf = (double*)pasub->vall, i = 0; i < pasub->nof; ++i) buf[i] = pw[i];
    
finish:
    gsl_matrix_free(A);
    gsl_matrix_free(V);
    gsl_vector_free(S);

    return 0;
}

static long correctOrbit(aSubRecord *pasub)
{
    const int NBPM = 396;
    const int NCOR = 360;
    /* solve Ax = b, A = U*S*V^T */
    /* a: matrix inversed */
    double *pMinv = (double *)pasub->a;
    /* b: X/Y orbit residual */
    double *pb = (double *)pasub->b;
    /* c: COR X/Y SP*/
    /* d,e: BPM/COR sel */
    const char *bpmsel = (char*)pasub->d;
    const char *corsel = (char*)pasub->e;

    /* row(bpm)/col(cor) of M, transpose for Minv */
    const long nvbpm = *(long*)pasub->f; 
    const long nvcor = *(long*)pasub->g;
    
    /* h,i: cor I setpoint */
    const double dImax = *(double*) pasub->h;
    const double dImin = *(double*) pasub->i;

    /* j: BPM weight */
    const double *pw = (double*) pasub->j;
    /* k: active status */
    const long active = *(long*) pasub->k;
    /* l: COR readback */
    const double *pcrb = (double*) pasub->l;
    /* fprintf(stderr, "Enabled: %d\n", active); */
    /* if (!status) return 0; */
    
    /* r: Kp, Ki, Kd, alpha */
    /* output */
    double *px  = (double *)pasub->vala;
    double *px0 = (double *)pasub->valb;

    const int m = 396;
    const int n = 360;
    int i = 0, j = 0, k = 0, iv = 0, jv = 0;
    double s1 = 0.0;
    double s2 = 0.0;
    double xmin = DBL_MAX;
    double xmax = DBL_MIN;
    double xstd = 0.0, xvar = 0.0, xrms = 0.0;
    /*    */
    double *pcdiff = (double*)pasub->vald;
    for (i = 0; i < pasub->nob; ++i) pcdiff[i] = pcrb[i] - pb[i];

             /* update weight */
    for (i = 0; i < NBPM; ++i) {
        if (bpmsel[i]) pb[i] *= pw[i];
    }
    
    /* fprintf(stderr, "MinvShape: %d %d (%d == %d, %d)\n", */
    /*         nvcor, nvbpm, nvcor*nvbpm, pasub->nea, pasub->noa); */
    
    for (iv = 0, i = 0; i < NCOR; ++i) {
        if (!corsel[i]) continue;
        double s = 0.0;
        for (jv = 0, j = 0; j < NBPM; ++j) {
            if (!bpmsel[j]) continue;
            s += pMinv[iv*NBPM+jv] * pb[j];
            ++jv;
        }
        /* take a negative */
        px0[i] = px[i] = -s;
        if(fabs(s) > xmax)  xmax = fabs(s);
        ++iv;
    }

    if (xmax < dImin || !active) {
        for (i = 0; i < pasub->nova; ++i) px[i] = 0.0;
    } else {
        for (i = 0; i < pasub->nova; ++i) {
            px[i] /= xmax / dImax;
        }
    }
    if (pasub->outc.type != CONSTANT) {
        /* final SP, even dI=0.0 */
        double *pxc = (double*)pasub->valc;
        double *c0 = (double*) pasub->c; /* input SP */
        for (i = 0; i < pasub->noc; ++i) {
            if (corsel[i] == 0) continue;
            pxc[i] = px[i] + c0[i];
        }
    }

    return 0;
}

epicsRegisterFunction(correctOrbit);
epicsRegisterFunction(solveSVD);
