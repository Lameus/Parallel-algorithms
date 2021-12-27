#include <iostream>
#include "mpi.h"


int main(int argc, char **argv)
{
	int rank, size, prev, next;
	
	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	float rbuf[2], sbuf[2];
	prev = rank - 1;
	next = rank + 1;
	if (rank == 0) prev = size - 1;
	if (rank == size - 1) next = 0;
	MPI_Recv_init(&rbuf[0], 1, MPI_FLOAT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	MPI_Recv_init(&rbuf[1], 1, MPI_FLOAT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	MPI_Send_init(&sbuf[0], 1, MPI_FLOAT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	MPI_Send_init(&sbuf[1], 1, MPI_FLOAT, next, 5, MPI_COMM_WORLD, &reqs[3]);
	for (int i = 0; i < size; i++) {
		sbuf[0] = rank;
		sbuf[1] = rank;

		MPI_Startall(4, reqs);
		// Nothing to add here, because uses Startall and Waitall
		MPI_Waitall(4, reqs, stats);

	}

	for (int i = 0; i < 4; i++)
		MPI_Request_free(&reqs[i]);

	std::cout << "Current process: " << rank << std::endl;
	std::cout << "Previous process: " << rbuf[0] << std::endl;
	std::cout << "Next process: " << rbuf[1] << std::endl;

	MPI_Finalize();
}