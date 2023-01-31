import numpy as np

"""
Gaussion elimination to solve

-2x + 0y + z = -4
-x + 7y + z = -50
5x - y + z = -26
 
Compare results with numpy.linalg.solve
"""
A= [[-2,0,1],[-1,7,1],[5,-1,1]]
b = [-4,-50,-26]
q= b[:]
V = A[:]
#forward elimination
for i in range(0,2):
    for j in range(i+1,3):
        factor = A[j][i]/A[i][i]
        A[j] = [A[j][k] - factor*A[i][k] for k in range(3)]
        b[j] = b[j] - factor*b[i]
        print(factor)
#back substitution
x = [0,0,0]
x[2] = b[2]/A[2][2]
for i in range(1,-1,-1):
    x[i] = (b[i] - sum([A[i][k]*x[k] for k in range(i+1,3)]))/A[i][i]

print(x)
print(np.linalg.solve(V,q))
