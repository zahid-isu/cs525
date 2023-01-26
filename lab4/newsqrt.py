"""
Demo using sqrt function defined by Newton's Method.
"""
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

# def main():
#     result = newsqrt(2, 1, 100, 1.0e-14)
#     print(result)

# if __name__ == "__main__":
#     main()