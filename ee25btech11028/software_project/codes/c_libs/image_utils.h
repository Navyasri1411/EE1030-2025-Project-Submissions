#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include "matrix.h"

unsigned char* load_image(const char *path, int *w, int *h, int *ch);
void save_image_gray(const char *path, double *A, int w, int h);
void image_to_matrix(unsigned char *img, int w, int h, int ch, double *A);
void matrix_to_image(double *A, int w, int h, unsigned char *img);

#endif

