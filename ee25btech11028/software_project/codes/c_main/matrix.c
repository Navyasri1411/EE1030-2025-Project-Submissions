#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

double* make_matrix(int rows, int cols) {
    double *M = (double*)malloc(sizeof(double) * rows * cols);
    if (!M) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return M;
}

void fill_zero(double *M, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) M[i] = 0.0;
}

void transpose_matrix(double *A, double *T, int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            T[INDEX(j, i, r)] = A[INDEX(i, j, c)];
}

void multiply_matrix(double *A, double *B, double *C, int r, int p, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double sum = 0.0;
            for (int k = 0; k < p; k++)
                sum += A[INDEX(i,k,p)] * B[INDEX(k,j,c)];
            C[INDEX(i,j,c)] = sum;
        }
    }
}

void multiply_vector(double *A, double *element, double *buffer, int r, int c) {
    for (int i = 0; i < r; i++) {
        double s = 0.0;
        for (int j = 0; j < c; j++)
            s += A[INDEX(i,j,c)] * element[j];
        buffer[i] = s;
    }
}

double dot_product(double *a, double *b, int size) {
    double s = 0.0;
    for (int i = 0; i < size; i++) s += a[i] * b[i];
    return s;
}

double vector_norm(double *v, int size) {
    double s = 0.0;
    for (int i = 0; i < size; i++) s += v[i] * v[i];
    return sqrt(s);
}

