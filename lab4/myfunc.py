
import math
import numpy as np

# sqrt function using Newton's method
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
    s = initial_guess
    for k in range(kmax):
        # if printshow>0:
            # print("Before iteration %2d, s = %20.15f" % (k,s))
        sold = s
        s = 0.5*(s + x/s)
        if (abs((s-sold)/x) < tol):
            break
    # if printshow>0:
    return s
    # print("After %d iterations, s = %20.15f" % (k+1,s))
    
# exp function using Taylor's serires expansion
def exp(x, initial_guess=1.0, kmax=100, tol=1.0e-14):
    """
    Compute the exponential of a number using Taylor series for e^x about x = x0
    Input: x: real number,
    kmax: integer, the maximum number of iterations, defaulf = 100
    Output: return exp of x
    """
    # store the value of e ≈2.7182818284590451
    e= 2.7182818284590451
    # find the nearest integer, let’s call it x0:
    x0= int(round(x))
    z=x-x0
    expx0= math.pow(e,x0)
    s=initial_guess

    for k in range (1,kmax): #updated loop

        sold=s
        s += (math.pow(z,k)/math.factorial(k)) # Taylor series expansion
        if abs((s-sold)/x)< tol: # if the term is too small than tol, then break
            break

    return expx0*s  # return the value of e^x


# natural log function using newton
def log(x, kmax=100, tol=1.0e-14):
    """
    Compute the natural log of a number using Newton’s method for f (s) = e^s −x 
    Input: x: real number,
    kmax: integer, the maximum number of iterations, defaulf = 100
    Output: return ln(x) 
    """
    #input
    s= x

    for k in range (kmax):
        sold =s 
        s = s - ((np.exp(s)-x)/np.exp(s)) # Newton's method

        if abs((sold-s))<tol:
            break

    return s    # return the value of ln(x)


def fact(input_num):
    """
    Compute the factorial of a number using simple loop
    Input: input_num: integer number,
    Output: return input_num! or n!
    """
    # check the input number if it's 0/negative first
    if input_num < 0:
        print("Sorry, factorial does not exist for negative numbers")
    elif input_num == 0:
        print("The factorial of 0 is 1")
    elif input_num>0:
        s = 1
        for k in range(1,input_num):
            s = s*(k+1) # loop to calculate the factorial
        return s
    
# def main():
#     result = sqrt(2, 1, 100, 1.0e-14)
#     print(result)
    
# if __name__ == "__main__":
#     main()
