#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <time.h>
#include <math.h>


int main()
{
    // Define matricx L
    matrix L = subtriangular(5,5); // subtriangular matrix L (NxN)
    print_matrix(&L);

    // Transpose of L = Ltr = L^T
    matrix Ltr = matrix_transpose(&L); 
    print_matrix(&Ltr);

    // A = L*L^T
    matrix A = matrix_mult(&L,&Ltr); print_matrix(&A); 

    // Random vector b (Nx1)
    vector b = random_vector(5);
    print_vector(&b);

    // Linear solve via Gaussian elimination
    vector soln = solve(&A,&b);
    print_vector(&soln);
}