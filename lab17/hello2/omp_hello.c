# include <stdio.h>
# include <stdlib.h>
# ifdef _OPENMP
# include <omp.h>
# endif

int main(int argc , char* argv [])
{
    void usage ( const char* prog_name );
    void hello ( const int thread_count );

    if (argc != 2) { usage (argv [0]); }
    const int thread_count = strtol (argv [1] , NULL , 10);
    if ( thread_count <= 0)
    { usage (argv [0]); }

    printf ("\n");
    # pragma omp parallel num_threads ( thread_count )
    hello ( thread_count );
    printf ("\n");

    return 0;
} 

void usage ( const char * prog_name )
{
    fprintf (stderr , "usage : %s <thread_count >\n", prog_name );
    fprintf (stderr , " thread_count should be positive \n");
    exit (1);
}
void hello ( const int thread_count )
{
# ifdef _OPENMP
    const int my_rank = omp_get_thread_num ();
    const int actual_thread_count = omp_get_num_threads ();
# else
    const int my_rank = 0;
    const int actual_thread_count = 1;
# endif
    if ( my_rank == 0 && thread_count != actual_thread_count )
    {
        fprintf (stderr , " Number of threads started != %i\n",
        thread_count );
    }
    printf (" Hello from thread %i of %i\n", my_rank +1,
    actual_thread_count );
} 