// This source code is modified from Dr. Luo's lecture note on using OpenMP on Nova Cluster
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# include "matrix.h"
# ifdef _OPENMP
#   include <omp.h>
# endif

// The below code performs the 2-norm of a vector using fine-grain parallelism and coarse-grain parallelism 
// input: main.exe thread_count N (thread_count= how many threads are being used, N= size of the vector)
// output: 2-Norm of the vctor, thread_count , clock_time  (thread_count= how many threads are being used, clock_time= time to run the code)
// thread_count>0, loop_count>0

int main(int argc , char* argv [])
{
    void usage ( const char* prog_name );
    void coarseg (int argc , char* argv []);
    // check the command line arguments
    if (argc != 3) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    if ( thread_count <= 0)
    { usage (argv [0]); }
    srand ( time(NULL) );
    
    vector x = new_vector (N);

    // initialize the vector v
    # pragma omp parallel for num_threads ( thread_count ) 
    for (int i=1; i <=N; i++)
    { vget(x,i) = 1.0; }
    double norm = 0.0;

    // compute the 2-norm of the vector v using fine-grained parallelism
    const double time1 = omp_get_wtime ();
    # pragma omp parallel num_threads (thread_count)
    {
        #pragma omp for reduction(+:norm)
        for (int i=1; i <=N; i++)
        { norm += (vget(x,i)*vget(x,i)); }

        #pragma omp single // only one thread will execute this
        norm = sqrt(norm);

        #pragma omp for
        for (int i=1; i <=N; i++)
        { vget(x,i)= vget(x,i)/norm; }
    
    }
    
    const double time2 = omp_get_wtime ();
    const double clock_time = time2 - time1 ;
    
    printf("\n ================ fine-grain parallelism ================= ");
    printf("\n N = %i, norm=%12.5e,  with %i threads , clock_time = %11.5e (sec)\n",N, norm, thread_count , clock_time );

    delete_vector (&x); // called coarse-grain parallelism 
    coarseg(argc, argv);
    return 0;
}


void usage ( const char * prog_name )
{
    fprintf (stderr , "usage : %s <thread_count > <matrix size >\n", prog_name );
    fprintf (stderr , " thread_count should be positive \n");
    fprintf (stderr , " N should be positive \n");
    exit (1);
}

void coarseg (int argc , char* argv [])
{

    const int thread_count = strtol (argv [1] , NULL , 10);
    const int N = strtol (argv [2] , NULL , 10);
    srand ( time(NULL) );
    
    vector x = new_vector (N);

    // initialize the vector v
    # pragma omp parallel for num_threads ( thread_count ) 
    for (int i=1; i <=N; i++)
    { vget(x,i) = 1.0; }
    double norm = 0.0;

    // compute the 2-norm of the vector v using corse-grain parallelism
    const double time1 = omp_get_wtime ();
    # pragma omp parallel num_threads (thread_count)
    {
        // split the work among threads
        const int my_rank = omp_get_thread_num ();
        const int N_per_thread = N/ thread_count ;
        const int istart = my_rank * N_per_thread + 1;
        const int iend = ( my_rank +1) *( N_per_thread );

        double norm_thread = 0.0;
        for (int i= istart ; i <= iend; i++)
        { norm_thread += (vget(x,i)* vget(x,i)); }

        # pragma omp critical
        norm += norm_thread ;

        # pragma omp barrier // stop until all threads reach here
        # pragma omp single // only one thread will execute the sqrt
        norm = sqrt(norm);

        # pragma omp barrier // needed here
        for (int i= istart ; i <= iend; i++)
        { vget(x,i) = vget(x,i)/norm; }
    
    }
    
    const double time2 = omp_get_wtime ();
    const double clock_time = time2 - time1 ;
    printf(" \n ================ coarse-grain parallelism =================");
    printf("\n N=%i, norm=%12.5e,  with %i threads , clock_time = %11.5e (sec)\n", N, norm, thread_count , clock_time );
    delete_vector (&x);
}

