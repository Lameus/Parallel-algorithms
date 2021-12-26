#include <iostream>
#include <mpi.h>

using namespace std;
 

int main(int argc, char* argv[])
{
    double* x, * y, * x_part, * y_part;
    double n = 1000000;
    
    x = (double*)calloc(n, sizeof(double)); // first vector
    y = (double*)calloc(n, sizeof(double)); // second

    double n_part;
    double product, part_product;
    int size, rank, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        // initializing of vectors
        for (i = 0; i < n; i++) { x[i] = 1; y[i] = 1;}
    }

    // Initilize parts for each thread
    n_part = n / size;
    x_part = (double*)calloc(n_part, sizeof(double));
    y_part = (double*)calloc(n_part, sizeof(double));

    // Sending equal parts of vectors
    MPI_Scatter(x, n_part, MPI_DOUBLE, x_part, n_part, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, n_part, MPI_DOUBLE, y_part, n_part, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    part_product = 0.0;
    for (i = 0; i < n_part; i++)
        part_product += x_part[i] * y_part[i];
    
    // Clean data for parts
    free(x_part); free(y_part);

    // Calculate total
    MPI_Reduce(&part_product, &product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        cout << product;
    }
    MPI_Finalize();

    return 0;
}