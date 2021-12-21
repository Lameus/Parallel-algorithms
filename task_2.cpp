#include <iostream>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

using namespace std;

// The function of allocating memory for a two-dimensional array
double** malloc_array(long int n)
{
	double** matrix = new double*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new double[n];
	return matrix;
}

// Memory free function
void free_array(double** matrix,long int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

// The function of initializing a matrix with random numbers from [0,1]
void rand_init_matrix(double** matrix,long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = rand() % 10;
}

// Matrix zeroing function
void zero_init_matrix(double** matrix, long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0.0 ;
}

int main(int argc, char* argv[1])
{
    int N = atoi(argv[1]);
	double** A, **B, **C;

// Memory allocation for matrices A, B, C
	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);

// Initialization of matrices
	rand_init_matrix(A, N);
	rand_init_matrix(B, N);
	zero_init_matrix(C, N);
	clock_t t;

    // Time for only 1 thread
	double time1 = omp_get_wtime();
    int threads = 1;
    #pragma omp parallel for num_threads(threads)
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				C[i][j] += A[i][k] * B[k][j];
	time1 = omp_get_wtime() - time1;
	//cout << "Time ikj loops is " << time1 / CLOCKS_PER_SEC << " seconds" << endl;
    
    // Calculation of the efficiency
    for (int thread = 2; thread < 11; thread++)
    {
        double time = omp_get_wtime();
        #pragma omp parallel for num_threads(threads)
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
                for (int j = 0; j < N; j++)
                    C[i][j] += A[i][k] * B[k][j];
        time = omp_get_wtime() - time;
        cout << "Number of threads: " << thread << " efficiency " << time / time1 <<  endl;
    }
/*
    // matrix multuplication result visualisation
        for (int i = 0; i < N; i++)
    {
        cout << "\n";
        for (int j = 0; j < N; j++)
        {
            cout << A[i][j];
            cout << ' ';
        }
    }
    cout << '\n';
        for (int i = 0; i < N; i++)
    {
        cout << "\n";
        for (int j = 0; j < N; j++)
        {
            cout << B[i][j];
            cout << ' ';
        }
    }
    cout << '\n';
    for (int i = 0; i < N; i++)
    {
        cout << "\n";
        for (int j = 0; j < N; j++)
        {
            cout << C[i][j];
            cout << ' ';
        }
    }
    */
// Freeing memory occupied by matrices A, B, C
	free_array(A, N);
	free_array(B, N);
	free_array(C, N);

	return 0;
}
