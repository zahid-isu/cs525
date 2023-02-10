# include <stdio.h>
# include <math.h>

// compute factorial of n using recursive function
int factorial(int n)
{
  if (n == 0)
    return 1;
  else if (n < 0)
    return 0;
  else
    return n * factorial(n-1);
}

// compute exponential of real number x using taylor series expansion

double exponential(double x)
{
  const double e= 2.7182818284590451;
  double sum = 0;
  int x0;
  double z;
  double expx0;
  double tol = 1e-14;
  //round the double to nearest integer
  x0 = round (x);
  z= x-x0;
  expx0 = pow(e,x0);
  //kmax=10
    for (int i = 0; i < 10; i++)
    {
        sum += pow(z,i)/factorial(i);
        if ((pow(z,i)/factorial(i)) < tol) //check if the term is less than tolerance
            break;
    }
    return expx0*sum;
  
}

int main()
{
// take input of a number and print its factorial
int n;
printf("Enter a number: ");
scanf("%d", &n);
int f = factorial(n);
printf("factorial(%d) = %d\n", n, f);

// take input of a number and print its exponential
printf("Enter an array of size 5:\n ");
double arrx[5];
for (int i = 0; i < 5; i++)
    scanf("%lf", &arrx[i]);

//print the array & save it in a datafile
FILE *out = fopen("output.txt", "w");
printf("The input array is: \n");
fprintf(out, "The input array is: \n");

for (int i = 0; i < 5; i++)
{    printf("%lf ", arrx[i]);
    fprintf(out, "arrx[%i]= %lf \n",i, arrx[i]);
}
// print exponential of each element of array & save in datafile
printf("\n Exponential of the array is: \n");
fprintf(out, "\n Exponential of the array is: \n");
for (int i = 0; i < 5; i++)
{   printf("exp(%lf) = %lf\n", arrx[i], exponential(arrx[i]));
    fprintf(out, "exp(arrx[%i]) = exp(%lf) = %lf\n",i, arrx[i], exponential(arrx[i]));
}
fclose(out);
return 0;
}