#include <iostream>
#include "mpi.h"


int main(int argc, char **argv)
{
	int rank, size, prev, next;
	int buf[2];
	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	prev = rank - 1;
	next = rank + 1;
	if (rank == 0) prev = size - 1;
	if (rank == size - 1) next = 0;
	
    // Send message to next thread, receive from previous
	MPI_Sendrecv(&rank, 1, MPI_INT, next, 5, &buf[0], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &stats[0]);
    // Reverse action
    MPI_Sendrecv(&rank, 1, MPI_INT, prev, 6, &buf[1], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &stats[1]);
	
	//Here you need to display the number of the current process, and what it receives from the previous and next processes.
	std::cout << "Current process: " << rank << std::endl;
	std::cout << "Previous process: " << buf[0] << std::endl;
	std::cout << "Next process: " << buf[1] << std::endl;


	MPI_Finalize();
}