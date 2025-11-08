#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "svd.h"

void power_iteration(double *M, int size, double *eigvals, double *eigvecs, int k) {
    double *W = make_matrix(size, size);
    for (int i = 0; i < size * size; i++) W[i] = M[i];
    double *b = malloc(sizeof(double) * size);
    double *buffer = malloc(sizeof(double) * size);

    for (int comp = 0; comp < k; comp++) {
        for (int i = 0; i < size; i++) b[i] = (double)rand() / RAND_MAX;
        double lambda = 0.0;

        for (int iter = 0; iter < 1000; iter++) {
            multiply_vector(W, b, buffer, size, size);
            double nrm = vector_norm(buffer, size);
            for (int i = 0; i < size; i++) b[i] = buffer[i] / nrm;
            multiply_vector(W, b, buffer, size, size);
            double new_lambda = dot_product(b, buffer, size);
            if (fabs(new_lambda - lambda) < 1e-8) break;
            lambda = new_lambda;
        }

        eigvals[comp] = lambda;
        for (int i = 0; i < size; i++)
            eigvecs[comp * size + i] = b[i];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                W[INDEX(i,j,size)] -= lambda * b[i] * b[j];
    }

    free(W);
    free(b);
    free(buffer);
}

void compute_svd(double *A, int rows, int cols, int k, double *S, double *U, double *V) {
    double *At = make_matrix(cols, rows);
    transpose_matrix(A, At, rows, cols);

    double *AtA = make_matrix(cols, cols);
    multiply_matrix(At, A, AtA, cols, rows, cols);

    double *eigvals = malloc(sizeof(double) * k);
    double *eigvecs = make_matrix(k, cols);

    power_iteration(AtA, cols, eigvals, eigvecs, k);

    for (int i = 0; i < k; i++)
        S[i] = sqrt(fabs(eigvals[i]));
    for (int i = 0; i < k * cols; i++) V[i] = eigvecs[i];

    double *v = malloc(sizeof(double) * cols);
    double *u = malloc(sizeof(double) * rows);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < cols; j++) v[j] = V[i * cols + j];
        multiply_vector(A, v, u, rows, cols);
        for (int r = 0; r < rows; r++)
            U[i * rows + r] = (S[i] > 1e-8) ? u[r] / S[i] : 0.0;
    }

    free(At);
    free(AtA);
    free(eigvals);
    free(eigvecs);
    free(v);
    free(u);
}

void reconstruct(double *U, double *S, double *V, int rows, int cols, int k, double *Ak) {
    fill_zero(Ak, rows, cols);
    for (int comp = 0; comp < k; comp++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Ak[INDEX(r,c,cols)] += S[comp] * U[comp * rows + r] * V[comp * cols + c];
            }
        }
    }
}

