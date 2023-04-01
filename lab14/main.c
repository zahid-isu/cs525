#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include <time.h>
#include <math.h>
// This code is taken from Dr. Luo's lecture notes, just modified to work with different eigenvalue functions


int main()
{
    // Get real symmetric matrix A
    matrix A = new_matrix(3,3);
    for(int i=1; i<=3; i++ )
    for (int j=1; j<=3; j++ )
    {
    mget(A,i,j) = 1.0*(i==j) + 1.0*(i-1==j) + 1.0*(j-1==i);
    }
    print_matrix(&A);
    int max_iter = 5; // maximum number of iterations
    double tol = 1e-6; // tolerance
    double lambda_pow = power_iteration(&A, max_iter, tol); // power_iteration
    eigenvalue
    double lambda_inv = inverse_power_iteration(&A, max_iter, tol, lambda_pow); //
    inverse_power_iteration eigenvalue
    double lambda_ray = rayleigh_quotient_iteration(&A, max_iter, tol); //
    rayleigh_quotient_iteration eigenvalue
    printf("power_iteration eigenvalue: %f\n", lambda_pow);
    printf("inverse_power_iteration eigenvalue: %f\n", lambda_inv);
    printf("rayleigh_quotient_iteration eigenvalue: %f\n", lambda_ray);
    // Note that the largest eigenvalue of A is 1+sqrt(2) and the closest value is
    obtained from the Rayleigh quotient iteration method
    return 0;
}