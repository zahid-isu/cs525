#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include <time.h>
// The below functions are taken from Prof. Luo's matrix.c file (CS525 class lecture).
// Added new functions to the bottom of the file, and modified the main.c file to use the new functions.
// create a new matrix

matrix new_matrix(const int rows, const int cols)
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    assert(rows>0);
    assert(cols>0);
    mat.val = (double*)malloc(sizeof(double)*rows*cols);
    for (int i=0; i<(rows*cols); i++)
    { mat.val[i] = 0.0; }
    return mat;
}
// print matrix
void print_matrix_full(const matrix* mat, char* varname)
{
    assert(mat->rows>0); assert(mat->cols>0);
    printf("\n %.100s =\n", &varname[1] );
    for(int i=1; i<=mat->rows; i++ )
    {
        printf(" | ");
        for(int j=1; j<=mat->cols; j++)
        {
            printf("%10.3e",mgetp(mat,i,j));
            if (j<mat->cols) {printf(", ");}
            else {printf(" ");}
        }
        printf("|\n");
    }
    printf("\n");
}
// matrix-matrix product
matrix matrix_mult(const matrix* A, const matrix* B)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    const int rowsB = B->rows; const int colsB = B->cols;
    assert(colsA==rowsB);
    matrix C = new_matrix(rowsA,colsB);
    for (int i=1; i<=rowsA; i++)
    for (int j=1; j<=colsB; j++)
    for (int k=1; k<=colsA; k++)
    { mget(C,i,j) += mgetp(A,i,k)*mgetp(B,k,j);}
return C;
}
// matrix subtraction
matrix matrix_sub(const matrix* A, const matrix* B)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    const int rowsB = B->rows; const int colsB = B->cols;
    assert(rowsA==rowsB); assert(colsA==colsB);
    matrix C = new_matrix(rowsA,colsB);
    for (int i=1; i<=rowsA; i++)
    for (int j=1; j<=colsB; j++)
    {
        mget(C,i,j) = mgetp(A,i,j)-mgetp(B,i,j);
    }
    return C;
}
// create vector
vector new_vector(const int size)
{
    vector vec;
    vec.size = size;
    assert(size>0);
    vec.val = (double*)malloc(sizeof(double)*size);
    for (int i=0; i<(size); i++)
    { vec.val[i] = 0.0; }
    return vec;
}
// print vector
void print_vector_full(const vector* vec, char* varname)
{
    assert(vec->size>0);
    printf("\n");
    printf(" %.100s =\n", &varname[1] );
    printf(" | ");
    for(int i=1; i<=vec->size; i++ )
    {
        printf("%10.3e",vgetp(vec,i));
        if (i<vec->size) {printf(", ");}
    }
    printf(" |^T\n\n");
}
// dot product of two vectors
double vector_dot_mult(const vector* x, const vector* y)
{
    const int size = x->size; assert(size==y->size);
    double z = 0.0;
    for (int i=1; i<=size; i++)
    { z += vgetp(x,i)*vgetp(y,i); }
    return z;
}
void print_scalar_full(const double* z, char* varname)
{
    printf("\n %.100s =\n", &varname[1] );
    printf(" %10.3e \n\n",*z);
}
// vector_scalar_mult
vector vector_scalar_mult(const double* a, const vector* x)
{
    const int size = x->size;
    vector Ax = new_vector(size);
    for (int i=1; i<=size; i++)
    {
        vget(Ax,i) = (*a)*vgetp(x,i);
    }
    return Ax;
}
// vector_norm
double vector_norm(const vector* x)
{
    const int size = x->size;
    double norm = 0.0;
    for (int i=1; i<=size; i++)
    {
        norm += vgetp(x,i)*vgetp(x,i);
    }
    return 1.0/sqrt(norm);
}
// matrix-vector product
vector matrix_vector_mult(const matrix* A, const vector* x)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = x->size;
    assert(cols==size);
    vector Ax = new_vector(rows);
    for (int i=1; i<=rows; i++)
    {
        double tmp = 0.0;
        for (int j=1; j<=size; j++)
        { tmp += mgetp(A,i,j)*vgetp(x,j); }
        vget(Ax,i) = tmp;
    }
    return Ax;
}
// matrix-scaler product
matrix matrix_scalar_mult(const double* a, const matrix* A)
{
    const int rows = A->rows; const int cols = A->cols;
    matrix aA = new_matrix(rows,cols);
    for (int i=1; i<=rows; i++)
    for (int j=1; j<=cols; j++)
    {
    mget(aA,i,j) = (*a)*mgetp(A,i,j);
    }
    return aA;
}
// Gaussian elimination with partial pivoting
vector solve(const matrix* A, const vector* b)
{
    const int rows = A->rows; const int cols = A->cols;
    const int size = b->size;
    assert(rows==cols); assert(rows==size);
    vector x = new_vector(rows);
    for (int i=1; i<=(size-1); i++) // LOOP OVER EACH COLUMN
    {
        // Select largest pivot in current column
        int p=i; double maxA = -100.0e0;
        for (int j=i; j<=size; j++)
        {
            double tmp = fabs(mgetp(A,j,i));
            if ( tmp > maxA ){ p = j; maxA = tmp; }
        }
        // See if matrix is singular
        if (maxA <= 1.0e-14)
        { printf(" Cannot invert system\n"); exit(1); }
        // Pivot (aka interchange rows)
        if (p!=i)
        {
            for (int j=1; j<=size; j++)
            {
                double tmp1 = mgetp(A,i,j);
                mgetp(A,i,j) = mgetp(A,p,j); mgetp(A,p,j) = tmp1;
            }
            double tmp2 = vgetp(b,i);
            vgetp(b,i) = vgetp(b,p); vgetp(b,p) = tmp2;
        }
        // Eliminate below diagonal
        for (int j=(i+1); j<=size; j++)
        {
            double dm = mgetp(A,j,i)/mgetp(A,i,i);
            for (int k=1; k<=size; k++)
            { mgetp(A,j,k) = mgetp(A,j,k) - dm*mgetp(A,i,k); }
            vgetp(b,j) = vgetp(b,j) - dm*vgetp(b,i);
        }
    }

    // Backward substitution
    vget(x,size) = vgetp(b,size)/mgetp(A,size,size);
    for (int j=1; j<=(size-1); j++)
    {
        double sum = 0.0e0;
        for (int k=(size-j+1); k<=size; k++)
        { sum = sum + mgetp(A,size-j,k)*vget(x,k); }
        vget(x,size-j) = (vgetp(b,size-j) - sum)/mgetp(A,size-j,size-j);
    }
    return x;
}
// Identity matrix
matrix identity (const int rows, const int cols)
{
    assert(rows==cols);
    matrix I = new_matrix(rows,cols);
    for (int i=1; i<=rows; i++)
    for (int j=1; j<=cols; j++)
    {
    if (i==j) { mget(I,i,j) = 1.0; }
    else { mget(I,i,j)= 0.0; }
    }
    return I;
}
// Subtriangular matrix
matrix subtriangular (const int rows, const int cols)
{
    assert(rows==cols);
    srand(time(NULL)); // seed random number generator
    matrix L = new_matrix(rows,cols);
    for (int i=1; i<=rows; i++)
    for (int j=1; j<=cols; j++)
    {
        if (i==j) { mget(L,i,j) = 1.0; }
        else { mget(L,i,j)= (double)rand() / RAND_MAX; }
    }
    return L;
}
// matrix transpose
matrix matrix_transpose(const matrix* A)
{
    const int rowsA = A->rows; const int colsA = A->cols;
    assert(colsA==rowsA);
    matrix C = new_matrix(rowsA,colsA);
    for (int i=1; i<=rowsA; i++)
        for (int j=1; j<=colsA; j++)
        {
        mget(C,i,j) = mgetp(A,j,i);
        }
        return C;
}
// create random vector
vector random_vector(const int size)
{
    vector vec;
    vec.size = size;
    assert(size>0);
    srand(time(NULL)); // seed random number generator
    vec.val = (double*)malloc(sizeof(double)*size);
    for (int i=0; i<(size); i++)
    { vec.val[i] = (double)rand() / RAND_MAX; }
    return vec;
}
// vector transpose
vector vector_transpose (const vector* x)
{
    const int size = x->size;
    vector xtr = new_vector(size);
    for (int i=1; i<=size; i++)
    { vget(xtr,i) = vgetp(x,i); }
    return xtr;
}
// Power iteration algorithm to find largest eigenvalue
double power_iteration(const matrix* A, const int max_iter, const double tol)
{
/* This routine runs power iteration algorithm to find largest eigenvalue
input = x(0) = random vector,
max_itr=5,
tolerence=1e-6,
matrix A = random real & symmetric matrix of size n x n
output = largest eignvalue (lamda) */
    const int rows = A->rows; const int cols = A->cols;
    assert(rows==cols);
    int k =0;
    int mstop=0;
    vector x = random_vector(rows);
    vector xtr = vector_transpose(&x);
    vector Ax = matrix_vector_mult(A,&x);
    double lambda_old = vector_dot_mult(&xtr,&Ax);
    double lambda = 0.0;
    while (mstop==0)
    {
        k=k+1;
        vector w = matrix_vector_mult(A,&x); // w = Ax
        double norm_w = vector_norm(&w); // 1/||w||
        vector x= vector_scalar_mult(&norm_w, &w); // x = w/||w||
        vector xtr = vector_transpose(&x);
        vector Ax = matrix_vector_mult(A,&x);
        lambda = vector_dot_mult(&xtr,&Ax); // lambda = x^T A x
        if (fabs(lambda-lambda_old) < tol || k==max_iter)
            { mstop=1; } // break
        lambda_old = lambda;
    };
    return lambda;
}
// Shifted inverse power iteration algorithm to find smallest eigenvalue
double inverse_power_iteration(const matrix* A, const int max_iter, const double tol, const double mu)
{
/* This routine runs shifted inverse power iteration algorithm to find largest
eigenvalue
input = x(0) = random vector,
max_itr=5,
tolerence=1e-6,
matrix A = random real & symmetric matrix of size n x n
output = largest eignvalue (lamda) */
    const int rows = A->rows; const int cols = A->cols;
    assert(rows==cols);
    int k =0;
    int mstop=0;
    vector x = random_vector(rows);
    vector xtr = vector_transpose(&x);
    vector Ax = matrix_vector_mult(A,&x);
    double lambda_old = vector_dot_mult(&xtr,&Ax);
    double lambda = 0.0;
    // const double mu = 0.123;
    while (mstop==0)
    {
        k=k + 1;
        matrix I= identity(rows, cols);
        matrix muI= matrix_scalar_mult(&mu, &I);
        matrix Amu = matrix_sub(A,&muI);
        vector w = solve(&Amu,&x); // (A-muI) w = x
        double norm_w = vector_norm(&w); // 1/||w||
        vector x= vector_scalar_mult(&norm_w, &w); // x = w/||w||
        vector xtr = vector_transpose(&x);
        vector Ax = matrix_vector_mult(A,&x);
        lambda = vector_dot_mult(&xtr,&Ax); // lambda = x^T A x
        if (fabs(lambda-lambda_old) < tol || k==max_iter)
            { mstop=1; } // break
        lambda_old = lambda;
    };
    return lambda;
}
// Rayleigh quotient iteration algorithm to find eigenvalue
double rayleigh_quotient_iteration(const matrix* A, const int max_iter, const double tol)
{
/* This routine runs Rayleigh quotient iteration algorithm to find largest
eigenvalue
input = x(0) = random vector,
max_itr=5,
tolerence=1e-6,
matrix A = random real & symmetric matrix of size n x n
output = largest eignvalue (lamda) */
    const int rows = A->rows; const int cols = A->cols;
    assert(rows==cols);
    int k =0;
    int mstop=0;
    vector x = random_vector(rows);
    vector xtr = vector_transpose(&x);
    vector Ax = matrix_vector_mult(A,&x);
    double lambda_old = vector_dot_mult(&xtr,&Ax);
    double lambda = 0.0;
    while(mstop==0)
    {
        k=k + 1;
        matrix I= identity(rows, cols);
        matrix lambdaI= matrix_scalar_mult(&lambda, &I);
        matrix Alambda = matrix_sub(A,&lambdaI);
        vector w = solve(&Alambda,&x); // (A-lamdaI) w = x
        double norm_w = vector_norm(&w); // 1/||w||
        vector x= vector_scalar_mult(&norm_w, &w); // x = w/||w||
        vector xtr = vector_transpose(&x);
        vector Ax = matrix_vector_mult(A,&x);
        lambda = vector_dot_mult(&xtr,&Ax); // lambda = x^T A x
        if (fabs(lambda-lambda_old) < tol || k==max_iter)
            { mstop=1; } // break
        lambda_old = lambda;
    };
    return lambda;
}