# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# include "matrix.h"
# ifdef _OPENMP
#   include <omp.h>
# endif

// The below code is taken from Dr. Luo's lecture note on using OpenMP on Nova Cluster
// input: main.exe thread_count N K (thread_count= how many threads are being used, loop_count= # of loop)
// output: thread_count , clock_time  (thread_count= how many threads are being used, clock_time= time to run the code)
// thread_count>0, loop_count>0

int main(int argc , char* argv [])
{
    void usage ( const char* prog_name );

    if (argc != 4) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    const int K = strtol (argv [3] , NULL , 10);
    printf(" N = %i", N);
    printf(" K = %i\n", K);
    if ( thread_count <= 0)
    { usage (argv [0]); }
    srand ( time(NULL) );
    vector w = new_vector (N);
    matrix a = new_matrix (N, K);
    vector v = new_vector (K);
    double norm = 0.0;

    // initialize the vector v
    for (int i=1; i <=K; i++)
    {
        vget(v,i) = (( double )(1))/(( double )(i));
        
    }

    // initialize the matrix a
    for (int i=1; i <=N; i++)
    {
        for (int j=1; j <=K; j++)
        {
            mget(a,i,j) = (( double )(1))/(( double )(j)+ (( double )(i))- (( double )(1)));

        }
    }

    const double time1 = omp_get_wtime ();
    # pragma omp parallel for num_threads ( thread_count )
    for (int i=1; i <=N; i++)
    {
        for (int j=1; j <=K; j++)   // set the K value <= large number (initial=200)
        {
            // matrix vector multiplication
            vget(w,i) += mget(a,i,j) * vget(v,j);

        }
        // calculate 1-norm of w using reduction
        # pragma omp critical
        norm += fabs(vget(w,i));

    }
    

    const double time2 = omp_get_wtime ();
    const double clock_time = time2 - time1 ;
    
    printf(" With %i threads , clock_time = %11.5e (sec)\n", thread_count , clock_time );
    printf(" 1-norm of w = %11.5e \n", norm );

    delete_vector (&w);
    delete_matrix (&a);
    delete_vector (&v);
    return 0;
}
void usage ( const char * prog_name )
{
    fprintf (stderr , "usage : %s <thread_count > <matrix size >\n",
    prog_name );
    fprintf (stderr , " thread_count should be positive \n");
    fprintf (stderr , " N should be positive \n");
    exit (1);
}

