
import math
import numpy as np
# exp function using taylor series
def expo(x, kmax=100):

    e= 2.7182818284590451

    x0= int(round(x))
    z=x-x0
    expx0= math.pow(e,x0)
    print(z, expx0)
    s=1

    for k in range (1,kmax): #updated loop

        sold=s
        s += (math.pow(z,k))/math.factorial(k)
        print(s)

        if (abs((s-sold)/x) < 1.0e-14):
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

# def main():
#     input_num = int(input("Enter a number to find its factorial: "))

#     expo(input_num)

# if __name__ == "__main__":
#     main()
# print("value nat", natlog(1, 10))
# print("value from numpy", np.log(1))
