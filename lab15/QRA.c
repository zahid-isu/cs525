#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "trimatrix.h"
// This code is taken from Dr. Luo's lecture notes, just modified to work with repeated QR decomposition
void QRA(trimatrix* T)
{
    // function declarations
    matrix QRdecomp(matrix* A);
    // get size
    const int N = T->rows; assert(N==T->cols);
    int k=1;
    int max_iter = 500; // maximum number of iterations, while k=infinite A(k) becomes diagonal w/ eigenvalues
    double tol = 1e-6;
    // find rayleigh quotient's eigenvalues
    // copy the matrix T into a new matrix S
    matrix S = new_matrix(N,N);
    mget(S,1,1) = tget(T,1,1);
    mget(S,1,2) = tget(T,1,2);
    for (int i=2; i<=(N-1); i++)
    {
        mget(S,i,i-1) = tget(T,i,i-1);
        mget(S,i,i) = tget(T,i,i);
        mget(S,i,i+1) = tget(T,i,i+1);
    }
    mget(S,N,N-1) = tget(T,N,N-1);
    mget(S,N,N) = tget(T,N,N);
    double lambda_ray = rayleigh_quotient_iteration(&S, max_iter, tol);
    if (N==1)
    { return; }
    else
    {
        // repeatedly apply QR decomposition until T is diagonal for large k values
        // for k=1,2, .. do Q(k)R(k)= A(k−1) and A(k)=R(k)Q(k)
        // until A(k) is diagonal
        // then A(k) is the eigenvalues of the original matrix A
        for (k=1; k<= max_iter; k++)
        {
            // copy the matrix T into a new matrix R
            matrix R = new_matrix(N,N);
            mget(R,1,1) = tget(T,1,1);
            mget(R,1,2) = tget(T,1,2);
            for (int i=2; i<=(N-1); i++)
            {
                mget(R,i,i-1) = tget(T,i,i-1);
                mget(R,i,i) = tget(T,i,i);
                mget(R,i,i+1) = tget(T,i,i+1);
            }
            mget(R,N,N-1) = tget(T,N,N-1);
            mget(R,N,N) = tget(T,N,N);
            // QR factorization of R
            matrix Q = QRdecomp(&R);
            // print Q
            // print_matrix(&Q);
            // Multiply Q and R in reverse order
            // and store in a new tridiagonal matrix
            delete_trimatrix(T);
            *T = matrix_mult_to_trimatrix(&R,&Q);
            // check if T is diagonal
            int is_diagonal = 0;
            for (int i=0; i<=N; i++)
            {
                for (int j=0; j<=N; j++)
                {
                    if (i!=j && tget(T,i,j) == 0.0)
                    {
                        is_diagonal = 1; // T is diagonal
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            // Now, if the eignevalues are close enough to rayleigh quotient's eigenvalues, break
            int flag = 0;
            for (int i=1; i<=N; i++)
            {
                if (fabs(tget(T,i,i) - lambda_ray) < tol && is_diagonal == 0)
                {
                    flag = 1;
                    printf("Eigenvalues are close enough to rayleigh quotient's eigenvalues\n");
                    break;
                }
                else
                {
                    continue;
                }
            }
            // delete Q & R matrices
            delete_matrix(&R);
            delete_matrix(&Q);
            if (flag == 1)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        printf("Rayleigh quotient's eigenvalue: %f\n", lambda_ray);
    }
}