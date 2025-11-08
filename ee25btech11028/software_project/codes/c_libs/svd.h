#ifndef SVD_H
#define SVD_H

void power_iteration(double *M, int size, double *eigvals, double *eigvecs, int k);
void compute_svd(double *A, int rows, int cols, int k, double *S, double *U, double *V);
void reconstruct(double *U, double *S, double *V, int rows, int cols, int k, double *Ak);

#endif

