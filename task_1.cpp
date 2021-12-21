#include <iostream>
#include <omp.h>
#include <ctime>

int find_max(int arr[], int len, int threads)
{
    int maximum_element = arr[0]; // first initiation
    #pragma omp parallel for reduction(max:maximum_element) num_threads(threads)
    for (int i = 0; i < len; i++)
    {
        maximum_element = maximum_element > arr[i] ? maximum_element : arr[i];
    }
    return maximum_element;
}

int* get_array(int len)
{
    int* array = new int[len];
    for(int i = 0; i < len; i++)
        array[i] = rand() % len;
    
    return array;
}

int main(int argc, char* argv[1])
{
    int len = atoi(argv[1]); // Extract vector's len
    int* arr = get_array(len);
    for (int num_threads = 1; num_threads <= 10; num_threads++)
    {
        double time = omp_get_wtime();
        int max_elem = find_max(arr, len, num_threads);
        std::cout << "Maximum element is: " << max_elem << " Time: " << (omp_get_wtime() - time) << "  Num_threads: " << num_threads;
        std::cout << "\n";
    } 
    return 0;
}