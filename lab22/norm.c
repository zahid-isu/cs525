# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mpi.h>
# include <math.h>
# include "matrix.h"


""" This perform the normalization of a vector using MPI 
The vector is divided into N/np parts, where np is the number of processors
The vector is filled with 1.0
The 2-norm of the vector is computed
The vector is normalized by dividing each element by the 2-norm on the local processors. Source code courtesy: Prof. Luo's class notes. """


int main(int argc , char* argv [])
{
    // Setup MPI code
    int comm_sz , my_rank ;
    MPI_Init (NULL ,NULL);
    MPI_Comm_size ( MPI_COMM_WORLD , & comm_sz );
    MPI_Comm_rank ( MPI_COMM_WORLD , & my_rank );

    // Grab the global N parameter
    // and set the local N parameter
    int N;
    void get_input (int argc , char* argv [],
                    const int my_rank ,
                    const int comm_sz ,
                    int* N);
    get_input (argc ,argv ,my_rank ,comm_sz ,&N);

    const int N_local = N/ comm_sz ; // divide N by the number of processors
    // Get time
    double time_start ;
    if ( my_rank ==0)
    { time_start = MPI_Wtime (); }

    // Create partial vector on current processor
    vector v_local = new_vector ( N_local );


    // Fill partial vector with value = 1.0
    for (int i=1; i <= N_local ; i++)
    { vget(v_local,i)=1.0; }
    

    // Compute 2-norm squared of local vector
    double norm_squared ;
    double norm_squared_local = pow(vget(v_local ,1) ,2);
    for (int i=2; i <= N_local ; i++)
    { norm_squared_local += pow(vget(v_local ,i) ,2); }

    // Add local norm results to get the global norm on Processor 0
    if ( my_rank != 0)
    {
        MPI_Send (& norm_squared_local ,1, MPI_DOUBLE ,0,0,
        MPI_COMM_WORLD );
        // MPI_Send (&v_local ,N_local , MPI_DOUBLE ,0,0, MPI_COMM_WORLD );
    }
    else
    {
        norm_squared = norm_squared_local ;
        for (int i=1; i< comm_sz ; i++)
        {
            MPI_Recv (& norm_squared_local ,1, MPI_DOUBLE ,i,0,
            MPI_COMM_WORLD , MPI_STATUS_IGNORE );
            // MPI_Recv (&v_local ,N_local , MPI_DOUBLE ,i,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
            norm_squared += norm_squared_local ;
        }
    }
    // Normalize the local vectors on Local processors
    for (int i=1; i <= N_local ; i++)
    {
        vget(v_local,i) /= sqrt(norm_squared);
    }
    

    // Print answer to screen
    if ( my_rank ==0)
    {
        double time_end = MPI_Wtime ();
        double time_elapsed = time_end - time_start ;
        printf("NP = %2i, N = %i, norm_squared = %20.13e, norm = %20.13e\n",
                comm_sz ,N, norm_squared ,sqrt(norm_squared));
        printf("\nElapsed time = %20.13e\n",
                time_elapsed );
        // print the first and last element of the normalized Local vector
        printf("\nFirst element v[1] = %20.13e, Last element v[N] = %20.13e\n\n",
                vget(v_local,1),vget(v_local ,N_local));

    }

    delete_vector (&v_local);

    // End program
    MPI_Finalize ();
    return 0;
}
void get_input (int argc , char* argv [],
                const int my_rank ,
                const int comm_sz ,
                int* N)
{
    void usage ( const char * prog_name );
    if ( my_rank ==0)
    {
        if (argc != 2) { usage (argv [0]); }

        *N = strtol (argv [1] , NULL , 10);
        if (*N <=0) { usage (argv [0]); }
        if (*N% comm_sz !=0) { usage (argv [0]); }

        for (int i=1; i< comm_sz ; i++)
        {
        MPI_Send (N,1, MPI_INT , i,0, MPI_COMM_WORLD );
        }
    }
    else
    {
    MPI_Recv (N,1, MPI_INT ,0,0, MPI_COMM_WORLD ,
    MPI_STATUS_IGNORE );
    }
}

void usage ( const char * prog_name )
{
    fprintf (stderr ," usage : %s <N >\n",prog_name );
    fprintf (stderr ," N should be positive \n");
    fprintf (stderr ," N should be exactly divisible "
    "by the number of processors \n");
    exit (1);
}

