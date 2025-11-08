#include <stdio.h>
#include <stdlib.h>

//  Define these macros once (and ONLY here)
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include "image_utils.h"

unsigned char* load_image(const char *path, int *w, int *h, int *ch) {
    unsigned char *img = stbi_load(path, w, h, ch, 0);
    if (!img)
        fprintf(stderr, "Failed to load %s: %s\n", path, stbi_failure_reason());
    return img;
}

void save_image_gray(const char *path, double *A, int w, int h) {
    unsigned char *out = malloc(w * h);
    matrix_to_image(A, w, h, out);
    stbi_write_jpg(path, w, h, 1, out, 90);
    free(out);
}

void image_to_matrix(unsigned char *img, int w, int h, int ch, double *A) {
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            int idx = (i * w + j) * ch;
            double gray = (ch == 1) ? img[idx]
                        : 0.299 * img[idx] + 0.587 * img[idx+1] + 0.114 * img[idx+2];
            A[INDEX(i,j,w)] = gray;
        }
}

void matrix_to_image(double *A, int w, int h, unsigned char *img) {
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            double v = A[INDEX(i,j,w)];
            if (v < 0) v = 0;
            if (v > 255) v = 255;
            img[INDEX(i,j,w)] = (unsigned char)v;
        }
}

