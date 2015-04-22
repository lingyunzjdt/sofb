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

#define NDEBUG

static long solveSVD(aSubRecord *pasub)
{
    int i, j, k, k1, k2;
    double *buf = NULL;
    /* A = U*S*V^T */
    /* a: full matrix */
    double *pA = (double *)pasub->a;
    /* b: active/inactive X/Y BPM */
    char *bsel = (char *)pasub->b;
    /* c: active/inactive X/Y Cor */
    char *csel = (char *)pasub->c;
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
    gsl_vector *work = gsl_vector_alloc(A->size2);
    /* SVD(A), where A is (m,n) and m >= n */
    /* gsl_linalg_SV_decomp_jacobi (&(Av.matrix), V, S); */
    /* gsl_linalg_SV_decomp_jacobi (A, V, S); */
    gsl_linalg_SV_decomp(A, V, S, work);

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
            if(m < n) {
                pMinv[j*A->size2 + i] = s;
            } else {
                pMinv[i*A->size1 + j] = s;
            }
        }
    }
    pasub->nevb = A->size2 * A->size1;
    /* fprintf(stderr, "Minv size: %ld %ld (%d)\n", A->size2, A->size1, pasub->nevb); */
    
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
    gsl_vector_free(work);
    return 0;
}

static long correctOrbit(aSubRecord *pasub)
{
    const int NBPM = 396;
    const int NCOR = 360;
    /* solve Ax = b, A = U*S*V^T */
    /* a: matrix inversed */
    double *pMinv = (double *)pasub->a;
    double *pM = (double *)pasub->n;
    /* b: X/Y orbit residual */
    double *pb = (double *)pasub->b;
    /* c: COR X/Y SP*/
    double *pcsp = (double*) pasub->c;
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
    char active = *(char*) pasub->k;
    /* l: COR readback */
    const double *pcrb = (double*) pasub->l;
    /* fprintf(stderr, "Enabled: %d\n", active); */
    /* if (!status) return 0; */
    const double obtXYmin = *(double*) pasub->m;
    
    /* r: Kp, Ki, Kd, alpha */
    /* output */
    double *px  = (double *)pasub->vala;        /* delta */
    double *px0 = (double *)pasub->valb;        /* delta0 */

 #ifndef NDEBUG
    fprintf(stderr, "enabled: %d\n", (int)active);
 #endif
    
    int m = 0;
    /* const int n = 360; */
    int i = 0, j = 0, k = 0, iv = 0, jv = 0;
    double s1 = 0.0;
    double s2 = 0.0;
    double xmin = DBL_MAX;
    double xmax = DBL_MIN;
    double xstd = 0.0, xvar = 0.0, xrms = 0.0;
    /*    */
    double *pcdiff = (double*)pasub->vald;
    for (i = 0; i < pasub->nob; ++i) {
        pcdiff[i] = pcrb[i] - pcsp[i];
        /* skip checking the following */
        /* if (i == 347) continue; */
        if (i == 329) continue;
        /* this will disable SOFB if the broken corr is not diabled */
        if (fabs(pcdiff[i]) > 0.01 && corsel[i]) active = 0;
    }

    /* update weight */
    for (m = 0, i = 0; i < NBPM; ++i) {
        if (!bpmsel[i]) continue;
        ++m;
        pb[i] *= pw[i];
        if (pb[i] < xmin) xmin = pb[i];
        if (pb[i] > xmax) xmax = pb[i];
        s1 += pb[i];
        s2 += pb[i] * pb[i];
    }
    s1 /= m;
    s2 /= m;
    /* average, rms, min, max, std, var*/
    ((double*)pasub->vale)[0] = s1;
    ((double*)pasub->vale)[1] = sqrt(s2);
    ((double*)pasub->vale)[2] = xmin;
    ((double*)pasub->vale)[3] = xmax;
    ((double*)pasub->vale)[4] = sqrt(s2 - s1*s1);
    ((double*)pasub->vale)[5] = s2 - s1 * s1;

    /* no correction is the maximum orbit residual is small enough */
    if (xmax < obtXYmin) active = 0;
    
    /* fprintf(stderr, "MinvShape: %d %d (%d == %d, %d)\n", */
    /*         nvcor, nvbpm, nvcor*nvbpm, pasub->nea, pasub->noa); */
    
    for (xmax = DBL_MIN, iv = 0, i = 0; i < NCOR; ++i) {
        double s = 0.0;
        for (jv = 0, j = 0; j < NBPM; ++j) {
            if (!bpmsel[j]) continue;
            s += pMinv[iv*nvbpm+jv] * pb[j];
            ++jv;
        }
        /* take a negative */
        px0[i] = px[i] = -s;

        if (!corsel[i]) {
            px0[i] = px[i] = 0.0;
            continue;
        }
        /* inc good bpm/cor */
        ++iv;
        if(fabs(s) > xmax)  xmax = fabs(s);
    }

    /* calculate the prediction */
    for (i = 0; i < NBPM; ++i) {
        double s = 0.0;
        for (j = k = 0; j < NCOR; ++j) {
            if (corsel[j] == 0) continue;
            s += px[k++] * dImax / xmax * pM[i*NCOR+j];
        }
        ((double*)pasub->valg)[i] = s;
    }

    /* active = 0; */
    if (xmax < dImin || !active) {
        for (i = 0; i < pasub->nova; ++i) px[i] = 0.0;
    } else if (xmax > dImax) {
        for (i = 0; i < pasub->nova; ++i) {
            px[i] /= xmax / dImax;
            /* if (fabs(px[i]) > dImax) px[i] *= dImax / fabs(px[i]); */
        }
    }

 #ifndef NDEBUG
    fprintf(stderr, "active= %d obtstd= %g\n", active, sqrt(s2 - s1*s1));
    fprintf(stderr, "calc dI= %g (max)", xmax);
    for (i = 0; i < pasub->nova; ++i) fprintf(stderr, " %g", px0[i]);
    fprintf(stderr, "\nscaled dI= ");
    for (i = 0; i < pasub->nova; ++i) fprintf(stderr, " %g", px[i]);
    fprintf(stderr, "\n");
 #endif
    
    
    if (pasub->outc.type != CONSTANT) {
        double s1 = 0.0;
        double s2 = 0.0;
        double xmin = DBL_MAX;
        double xmax = DBL_MIN;
        double xstd = 0.0, xvar = 0.0, xrms = 0.0;
        int m = 0;
        /* final SP, even dI=0.0 */
        double *pxc = (double*)pasub->valc;
        double *c0 = (double*) pasub->c; /* input SP */
        for (i = 0; i < pasub->noc; ++i) {
            if (corsel[i] == 0) continue;
            pxc[i] = px[i] + c0[i];

            /* statistics */
            if (pxc[i] < xmin) xmin = pxc[i];
            if (pxc[i] > xmax) xmax = pxc[i];
            s1 += pxc[i];
            s2 += pxc[i] * pxc[i];
            ++m;
        }
        s1 /= m;
        s2 /= m;
        /* average, rms, min, max, std, var*/
        ((double*)pasub->valf)[0] = s1;
        ((double*)pasub->valf)[1] = sqrt(s2);
        ((double*)pasub->valf)[2] = xmin;
        ((double*)pasub->valf)[3] = xmax;
        ((double*)pasub->valf)[4] = sqrt(s2 - s1*s1);
        ((double*)pasub->valf)[5] = s2 - s1 * s1;
        /* fprintf(stderr, "average: %g, std: %g\n", s1, sqrt(s2)); */
    } else {
        /* fprintf(stderr, "COR SP is not connected\n"); */
    }

    return 0;
}

epicsRegisterFunction(correctOrbit);
epicsRegisterFunction(solveSVD);
