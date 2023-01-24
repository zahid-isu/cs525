
import math
import numpy as np
# exp function using taylor series
def expo(x, kmax):

    e= 2.7182818284590451

    x0= int(round(x))
    z=x-x0
    expx0= math.pow(e,x0)
    s=0

    for k in range (kmax):

        
        s += (math.pow(z,k)/math.factorial(k))


        if abs((math.pow(z,k)/math.factorial(k))< 1e-14): # if the term is too small, then break
            break

    return expx0*s

# print("value my function", expo(2, 10))
# print("value from numpy", np.exp(2))

# natural log function using newton
def natlog(x, kmax):

    s= x

    for k in range (kmax):
        sold =s
        s = s - ((np.exp(s)-x)/np.exp(s))

        if abs((sold-s))<1e-14:
            break

    return s

# print("value nat", natlog(1, 10))
# print("value from numpy", np.log(1))
