#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// constant variables for the desired size of matrix 1
const size_t MAT1_X = 2;
const size_t MAT1_Y = 4;

// constant variables for the desired size of matrix 2
const size_t MAT2_X = 4;
const size_t MAT2_Y = 2;

int main() 
{
	// seed rand for randomly filling the matrices
	srand(time(NULL));
	
	// define the matrices to the variables mat1 and mat2
	int mat1[MAT1_X][MAT1_Y];
	int mat2[MAT2_X][MAT2_Y];
	
	// define the result matrix
	int result_mat[MAT1_X][MAT2_Y];
	
	// zero result matrix
	for(int i = 0; i < MAT1_X; i++)
	{
		for(int j = 0; j < MAT2_Y; j++)
		{
			result_mat[i][j] = 0;
		}
	}
	
	// fill in mat1 with random positive integers <= 100
	for(int i = 0; i < MAT1_X; i++)
	{
		for(int j = 0; j < MAT1_Y; j++)
		{
			mat1[i][j] = (rand() % 10) + 1;
		}
	}
	
	// fill in mat2 with random positive integers <= 100
	for(int i = 0; i < MAT2_X; i++)
	{
		for(int j = 0; j < MAT2_Y; j++)
		{
			mat2[i][j] = (rand() % 10) + 1;
		}
	}
	
	// if the matrices can be multiplied, do it
	if(MAT1_Y == MAT2_X)
	{
		for(int i = 0; i < MAT1_X; i++)
		{
			for(int j = 0; j < MAT2_Y; j++)
			{
				for(int k = 0; k < MAT1_Y; k++)
				{
					result_mat[i][j] += mat1[i][k] * mat2[k][j];
				}
			}
		}
		
	} else
	{
		cout << "the dimensions of the two matrices don't allow multiplication" << endl;
	}
	
	
	// print the matrices for testing purposes
	for(int i = 0; i < MAT1_X; i++)
	{
		for(int j = 0; j < MAT1_Y; j++)
		{
			cout << mat1[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < MAT2_X; i++)
	{
		for(int j = 0; j < MAT2_Y; j++)
		{
			cout << mat2[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
	
	for(int i = 0; i < MAT1_X; i++)
	{
		for(int j = 0; j < MAT2_Y; j++)
		{
			cout << result_mat[i][j] << " ";
		}
		cout << endl;
	}
}