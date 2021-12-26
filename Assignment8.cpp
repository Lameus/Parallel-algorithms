#include <iostream>
#include <mpi.h>

using namespace std;

#define MAX_SIZE 1000000 
#define NTIMES 10


int main(int argc, char **argv)
{
	int rank, size;
	MPI_Status status;
    double t_start, sum_time = 0.0, time_finish;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Message size increasing by 10 on each iteration

    for (int message_size = 1; message_size <= MAX_SIZE; message_size *= 10) {
        int msg[MAX_SIZE];
        // Initialize message's elements by random
        for (int i = 0; i < MAX_SIZE; i++) {
            msg[i] = rand() % 10;
        }
        
        t_start = MPI_Wtime();

            if (rank == 0) {

                MPI_Send(&msg[0], message_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(msg, message_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

            } else if(rank == 1) {                               
                MPI_Recv(msg, message_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                MPI_Send(msg, message_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }

        if (rank == 0) { 
            
            for (int i = 0; i < NTIMES; i++) // Loop for time averaging
		    time_finish = MPI_Wtime();
            sum_time = time_finish - t_start;

            cout<<"Message size: "<<message_size * sizeof(int)<<" bytes. "<<endl;

            double L = message_size * sizeof(int) / (1024.0 * 1024.0);
            double bandwidth = 2.0 * L * (double)NTIMES / sum_time;
            double latency = sum_time/(double)NTIMES/2.0;
            cout << "The bandwidth is: " << bandwidth << "Mb/s " << " and latency: " << latency <<endl << endl;
        }
    }

	MPI_Finalize();
    return 0;
}