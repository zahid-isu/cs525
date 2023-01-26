import math
import numpy as np

"""
Calculate factorial
"""

def myfact(input_num):
    
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
    

# def main():
#     input_num = int(input("Enter a number to find its factorial: "))
#     fact_result = factorial(input_num)
#     print("The factorial of", input_num, "is", fact_result)

# if __name__ == "__main__":
#     main()

