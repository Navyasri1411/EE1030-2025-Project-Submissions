#ifndef MATRIX_H
#define MATRIX_H

double* make_matrix(int rows, int cols);
void fill_zero(double *M, int rows, int cols);
void transpose_matrix(double *A, double *T, int r, int c);
void multiply_matrix(double *A, double *B, double *C, int r, int p, int c);
void multiply_vector(double *A, double *element, double *buffer, int r, int c);
double dot_product(double *a, double *b, int size);
double vector_norm(double *v, int size);

#define INDEX(row,col,cols) ((row)*(cols)+(col))

#endif

