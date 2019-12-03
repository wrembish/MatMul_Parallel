#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// constant variables for the desired size of matrix 1
const size_t MAT_SIZE = 835;

void print_matrix(int* matrix)
{
	for(int i = 0; i < MAT_SIZE; i++)
	{
		int x_loc = i * MAT_SIZE;
		for(int j = 0; j < MAT_SIZE; j++)
		{
			cout << matrix[x_loc+j] << " ";
		}
		cout << endl;
	}
};

int main() 
{
	// take start time of whole program
	auto prog_start = high_resolution_clock::now();
	// seed rand for randomly filling the matrices
	srand(time(NULL));
	
	// define the matrices to the variables mat1 and mat2
	int mat1[MAT_SIZE*MAT_SIZE];
	int mat2[MAT_SIZE*MAT_SIZE];
	
	// define the result matrix
	int result_mat[MAT_SIZE*MAT_SIZE];
	
	// zero result matrix
	#pragma acc loop
	for(int unsigned i = 0; i < MAT_SIZE*MAT_SIZE; i++)
	{
		result_mat[i] = 0;
	}
	
	// fill in mat1 with random positive integers <= 100
	#pragma acc loop
	for(int unsigned i = 0; i < MAT_SIZE; i++)
	{
		int x_loc = i * MAT_SIZE;
		for(int unsigned j = 0; j < MAT_SIZE; j++)
		{
			mat1[x_loc+j] = (rand() % 100) + 1;
		}
	}
	
	// fill in mat2 with random positive integers <= 100
	#pragma acc loop
	for(int unsigned i = 0; i < MAT_SIZE; i++)
	{
		int x_loc = i * MAT_SIZE;
		for(int unsigned j = 0; j < MAT_SIZE; j++)
		{
			mat2[x_loc+j] = (rand() % 100) + 1;
		}
	}
	
	// multiply the matrices
	int unsigned i, j, k, x_loc, y_loc, total;
	//#pragma omp parallel for ordered schedule(auto) shared(result_mat) private(i, j, k, x_loc, y_loc, total)
	#pragma acc data copyout(result_mat[0:MAT_SIZE*MAT_SIZE]) copyin(mat1[0:MAT_SIZE*MAT_SIZE], mat2[0:MAT_SIZE*MAT_SIZE])
	#pragma kernels
	for(i = 0; i < MAT_SIZE; i++)
	{
		x_loc = i * MAT_SIZE;
		for(j = 0; j < MAT_SIZE; j++)
		{
			y_loc = j * MAT_SIZE;
			total = 0;
			for(k = 0; k < MAT_SIZE; k++)
			{
				total += mat1[x_loc+k] * mat2[y_loc+k];
			}
			result_mat[x_loc+j] = total;
		}
	}
	
	// take end time of whole program
	auto prog_stop = high_resolution_clock::now();
	
	// get the difference in time between program start and finish
	auto prog_duration = duration_cast<microseconds>(prog_stop - prog_start);
	cout << "time taken(program): " << prog_duration.count() << " microseconds." << endl;
}
