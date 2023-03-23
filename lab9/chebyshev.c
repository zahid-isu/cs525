#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// chebyshev polynomial using switch case


int main()
{
    const int Nmax = 5;
    int N;

    // read-in polynomial degree
    printf("\n Input polynomial degree (0-%i): ",Nmax);
    scanf("%i", &N);
    if (N<0 || N>Nmax)
    {
        printf(" Invalid value N = %i.\n",N);
        printf(" N must satisfy: 0 <= N <= %i\n\n",Nmax);
        exit(1);
    }
    printf("\n");



    double b[Nmax+1];
    for (int i=0; i<=N; i++)
        {
        printf(" Set b[%i]: ",i);
        scanf("%lf", &b[i]);
        }
    printf("\n");

    // set x-coordinates
    const int NumPts = 30;
    double x[NumPts];
    for (int i=0; i<NumPts; i++)
        {
        x[i] = -1.0 + i*(2.0/(1.0*(NumPts -1)));
        }

    double y[NumPts]; // y(x) output values
    //sample polynomial
    void SamplePoly(const int N,
                    const int NumPts,
                    const double b[],
                    const double x[],
                    double y[]);
     SamplePoly(N,NumPts,b,x,y);

    // Write to file
    void WritePoly(const int NumPts,
                const double x[],
                double y[]);
    WritePoly(NumPts,x,y);

    // Call python script to plot
    system("python3 PlotPoly.py");

    return 0;

}   
    void WritePoly(const int NumPts, // write to file
                const double x[],
                double y[])
    {
        FILE *fp;
        fp = fopen("poly.data", "w");
        for (int i=0; i<NumPts; i++)
        {
            fprintf(fp, "%f,%f\n", x[i], y[i]); 
        }
        fclose(fp);
    }

    void SamplePoly(const int N, // polynomial degree
                    const int NumPts, // number of x point values
                    const double b[], // polynomial coefficients
                    const double x[], // x point values
                    double y[]) // y(x) output values
    {
        
        for (int i=0; i<NumPts; i++)
        {
            const double a = x[i]; double phi; y[i] = b[0];
            for (int k=1; k<=N; k++)
            {   printf("%f, %f \n", x[i], y[i]);

                switch(k)
                {
                    case 1:
                    phi = 1.0*a; break;
                    case 2:
                    phi = (2.0*pow(a,2) -1.0); break;
                    case 3:
                    phi =(4.0*pow(a,3) -3.0*a); break;
                    case 4:
                    phi =(8.0*pow(a,4)-8.0*pow(a,2)+1); break;
                    case 5:
                    phi =(16.0*pow(a,5)-20.0*pow(a,3)+5.0*a); break;
                    default:
                    printf("\n Error \n."); exit(1);
                }
                y[i] += b[k]*phi;
            }
        }

    }


    



