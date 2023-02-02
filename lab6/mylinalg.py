import numpy as np

"""
(Gaussian elimination code snippet is taken from the previous lab assignment[Prof. Luo's code])
Gauss elimination (no partial pivoting) 
solve linear system Ax = b with a given example 
A size (nptxnpt) matrix
b size (nptx1) vector

"""
def gauss_elemination (A,b, npt):
    print('Input matices are:')
    print("A", A)
    print("b", b)

    num_rows = npt
    num_cols = npt

    #main loop 
    for col in range(num_cols-1):
        for row in range(col+1,num_rows):
            m = (A[row][col]/A[col][col])
            A[row][col:] = A[row][col:] - m*A[col][col:]
            b[row] = b[row] - m*b[col]

    #back substituion
    x= np.zeros(npt)
    x[num_rows-1] = b[num_rows-1]/A[num_rows-1][num_cols-1]
    for row in range(num_rows-2,-1,-1):
        x[row] = (b[row] - np.dot(A[row][row+1:],x[row+1:]))/A[row][row]

    return x #solution from Gaussian elimination