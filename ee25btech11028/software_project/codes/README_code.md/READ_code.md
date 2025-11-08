The project implements image compression using Singular Value Decomposition (SVD) based on the Power Iteration algorithm in the C programming language.
The complete program was divided into multiple source and header files for better modularity and clarity:

matrix.h / matrix.c –
These files include basic matrix operations such as matrix creation, transposition, multiplication, dot product, and normalization functions.
These are the mathematical building blocks required for performing SVD.

svd.h / svd.c –
These files contain the main logic for computing the Singular Value Decomposition.
The power_iteration() function finds the largest eigenvalues and eigenvectors of A^T A,
while compute_svd() and reconstruct() functions are used to compute singular values and reconstruct the compressed image matrix.

image_utils.h / image_utils.c –
These handle image input and output operations using the stb image library.
Functions like load_image(), save_image_gray(), image_to_matrix(), and matrix_to_image() are implemented here to convert between image pixels and numerical matrices.

main.c –
This file is the driver program. It reads the input image, converts it to a grayscale matrix, performs SVD compression using the functions in svd.c, reconstructs the image using only the top 
k
k singular values, and finally saves the compressed image as a new file.

Makefile –
The Makefile automates the compilation process. The project was compiled using the following command:
[gcc src/matrix.c src/svd.c src/image_utils.c src/main.c -o svd_image -O3 -lm -Iinclude]
After successful compilation
[./svd_image]
