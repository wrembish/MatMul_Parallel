// https://github.com/wrembish/MatMul_Parallel.git
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// constant variables for the desired size of matrix 1
const size_t MAT1_X = 835;
const size_t MAT1_Y = 835;

// constant variables for the desired size of matrix 2
const size_t MAT2_X = 835;
const size_t MAT2_Y = 835;

int main() 
{
	// take start time of whole program
	auto prog_start = high_resolution_clock::now();
	// seed rand for randomly filling the matrices
	srand(time(NULL));
	
	// define the matrices to the variables mat1 and mat2
	int mat1[MAT1_X][MAT1_Y];
	int mat2[MAT2_X][MAT2_Y];
	
	// define the result matrix
	int result_mat[MAT1_X][MAT2_Y];
	
	// zero result matrix
	#pragma acc loop
	for(int unsigned i = 0; i < MAT1_X; i++)
	{
		for(int unsigned j = 0; j < MAT2_Y; j++)
		{
			result_mat[i][j] = 0;
		}
	}
	
	// fill in mat1 with random positive integers <= 100
	#pragma acc loop
	for(int unsigned i = 0; i < MAT1_X; i++)
	{
		for(int unsigned j = 0; j < MAT1_Y; j++)
		{
			mat1[i][j] = (rand() % 100) + 1;
		}
	}
	
	// fill in mat2 with random positive integers <= 100
	#pragma acc loop	
	for(int unsigned i = 0; i < MAT2_X; i++)
	{
		for(int unsigned j = 0; j < MAT2_Y; j++)
		{
			mat2[i][j] = (rand() % 100) + 1;
		}
	}
	
	// if the matrices can be multiplied, do it
	if(MAT1_Y == MAT2_X)
	{
		//#pragma omp parallel for ordered schedule(auto) collapse(3)
		#pragma acc data copyout(result_mat[0:MAT1_X][0:MAT2_Y]), copyin(mat1[0:MAT1_X][0:MAT1_Y],mat2[0:MAT2_X][0:MAT2_Y])
		#pragma kernels
		for(int unsigned i = 0; i < MAT1_X; i++)
		{
			//#pragma acc loop
			for(int unsigned j = 0; j < MAT2_Y; j++)
			{
				//#pragma acc loop seq
				for(int unsigned k = 0; k < MAT1_Y; k++)
				{
					result_mat[i][j] += mat1[i][k] * mat2[k][j];
				}
			}
		}
		
	} else
	{
		cout << "the dimensions of the two matrices don't allow multiplication" << endl;
	}
	
	// take end time of whole program
	auto prog_stop = high_resolution_clock::now();
	
	// get the difference in time between program start and finish
	auto prog_duration = duration_cast<microseconds>(prog_stop - prog_start);
	cout << "time taken(program): " << prog_duration.count() << " microseconds." << endl;
}
