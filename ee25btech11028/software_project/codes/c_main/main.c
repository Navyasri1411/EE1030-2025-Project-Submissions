#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "stb_image.h"
#include "stb_image_write.h"

#include "matrix.h"
#include "svd.h"
#include "image_utils.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s k image1.jpg [image2.jpg ...]\n", argv[0]);
        return 1;
    }

    srand((unsigned)time(NULL));
    int k = atoi(argv[1]);

    for (int i = 2; i < argc; i++) {
        const char *fname = argv[i];
        int w, h, ch;
        unsigned char *img = load_image(fname, &w, &h, &ch);
        if (!img) continue;

        double *A = make_matrix(h, w);
        image_to_matrix(img, w, h, ch, A);

        int max_k = (h < w) ? h : w;
        if (k > max_k) k = max_k;

        double *S = malloc(sizeof(double) * k);
        double *U = make_matrix(k, h);
        double *V = make_matrix(k, w);
        double *Ak = make_matrix(h, w);

        compute_svd(A, h, w, k, S, U, V);
        reconstruct(U, S, V, h, w, k, Ak);

        char outname[256];
        snprintf(outname, sizeof(outname), "output_%d_k%d.jpg", i-1, k);
        save_image_gray(outname, Ak, w, h);

        printf("Saved compressed image: %s\n", outname);

        
        stbi_image_free(img);

        free(A);
        free(S);
        free(U);
        free(V);
        free(Ak);
    }

    printf("All done.\n");
    return 0;
}

