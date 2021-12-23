#include <iostream>
#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	int sequence[n]; // save sequence
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	sequence[0] = rank;
	bool asc_flag = true;
	if (rank == 0)
	{
		int previous = rank;
		for (i = 1; i < n; i++) 
		{
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,
			         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			int current = message;
			if (current < previous)
			{
				cout << "Sequence isn't strictly ascending " << endl;
				asc_flag = false;
				sequence[i] = current;
					for (int j = 0; j < i + 1; j++)
						{
							cout << "  " << sequence[j];
						}
				break;
			}
			else
			{
				sequence[i] = current;
			}
			previous = current;
		}
		if (asc_flag == true)
		{
			for (i = 0; i < n; i++)
			{
				cout << "Message from process " << sequence[i] << "\n" << endl;
			}
		}
	}
	else MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}