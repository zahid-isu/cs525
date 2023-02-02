import numpy as np
import matplotlib.pyplot as plt
import mylinalg as my

"""
Polynomial interpolation using Gaussian Elimination:
The main function is f= cos(x) and the polynomial is p(x) = a1*x^3 + a2*x^2 + a3*x + a4
The Gaussian Elimination is used to find the coefficients a= [a1, a2, a3, a4]
"""

# input A1 and b1 from the previous lab assignment

A1 = np.array([[-2,0,1],[-1.0,7,1],[5,-1,1]])
b1 = np.array([-4.0,-50,-26])

# input A and b for the lab6 assignment

xpts= np.array([-0.1, -0.02 , 0.02, 0.1])
A = np.array([[xpts[0]**3, xpts[0]**2, xpts[0], 1.0], [xpts[1]**3, xpts[1]**2, xpts[1], 1.0], [xpts[2]**3, xpts[2]**2, xpts[2], 1.0], [xpts[3]**3, xpts[3]**2, xpts[3], 1.0]])
b = np.array([np.cos(xpts[0]), np.cos(xpts[1]), np.cos(xpts[2]), np.cos(xpts[3])])

a = my.gauss_elemination(A,b,4) #solution from Gaussian elimination
print("Solution from the Gaussian Elemination :", a)

q = my.gauss_elemination(A1,b1,3) #check if Gaussian elimination works for lab5
print("Gaussian Elemination results for lab5:", q)


# Making the plot 
xp = np.linspace(-0.1, 0.1, 101)
f= np.cos(xp)
p = np.zeros(101) 
# a=[a1, a2, a3, a4]  comes from Gaussian elimination solution

for pw in range(3):

    p= p+ (xp**pw)* a[3-pw] #Polynomial from Gaussian Elimination

plt.plot( xp, f, 'r', xp, p, 'o')
plt.legend(['Main function f= cos(x)', 'Polynomial p(x) from Gaussian Elimination'])
plt.xlabel('x')
plt.ylabel('f(x) and p(x)')
plt.show()
