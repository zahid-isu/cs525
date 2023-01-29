
import math
import numpy as np
# exp function using taylor series

def sqrt (x, printshow=0, initial_guess=1.0, kmax=100, tol=1.0e-14):
    """
    Compute the square root of a number using Newton's method solving f(s) = s^2 - x
    Input: x: real number,
    kmax: integer, the maximum number of iterations
    Output: return sqrt of x
    """
    # convert input integer to float
    x = 1.0*x
    # check if input makes sense
    if x==0.0:
        return 0.0 
    elif x<0.0:
        print("ERROR: input × must be non-negative")
        return -1.0
        
    # main loop
    s = 1.0
    for k in range(100):
        # if printshow>0:
            # print("Before iteration %2d, s = %20.15f" % (k,s))
        sold = s
        s = 0.5*(s + x/s)
        if (abs((s-sold)/x) < tol):
            break
    # if printshow>0:
    return s
    # print("After %d iterations, s = %20.15f" % (k+1,s))
    

def exp(x, kmax=100):
    
    e= 2.7182818284590451

    x0= int(round(x))
    z=x-x0
    expx0= math.pow(e,x0)
    s=1.0

    for k in range (1,kmax): #updated loop

        sold=s
        s += (math.pow(z,k)/math.factorial(k))


        if abs((s-sold)/x)< 1e-14: # if the term is too small, then break
            break

    return expx0*s

# print("value my function", expo(2, 10))
# print("value from numpy", np.exp(2))

# natural log function using newton
def log(x,kmax=100):
    s= x

    for k in range (kmax):
        sold =s
        s = s - ((np.exp(s)-x)/np.exp(s))

        if abs((sold-s))<1e-14:
            break

    return s


def fact(input_num):
    
    # check the input number if it's 0/negative first
    if input_num < 0:
        print("Sorry, factorial does not exist for negative numbers")
    elif input_num == 0:
        print("The factorial of 0 is 1")
    elif input_num>0:
        s = 1
        for k in range(1,input_num):
            s = s*(k+1)
        return s
    

# print("value nat", natlog(1, 10))
# print("value from numpy", np.log(1))
