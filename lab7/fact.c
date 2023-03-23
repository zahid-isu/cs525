#include <stdio.h>

/* c code calculating factorial of a number */

int main() {
    int num, factorial = 1;

    // take input integer number = num
    printf("Enter an integer: ");
    scanf("%d", &num);
    
    // check if num is negative
    if (num < 0)
    {
        printf("Factorial of a negative number doesn't exist.\n");
    }
    // check if num is zero
    else if (num == 0)
    {
        printf("Factorial of a zero is 1.\n");
    }
    // calculate factorial of positive num
    else if (num > 0)
    {
        for (int i = 1; i <= num; ++i)
        {
            factorial *= i;
        }
        printf("Factorial of %d = %d \n", num, factorial);
    }

    return 0;
}
