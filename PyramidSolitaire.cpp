#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <algorithm>    // std::random_shuffle
using namespace std;

const int MAT_SIZE = 52;

int randomFunct(int x)
{    

	return rand()%x;
}

void printPyramid(int *matrix)
{
		
	// End of Declaration
	int post =0;
	for (int j =0 ; j<7;j++)
	{
			for (int m=6-j ; m>=0;m--)
				printf(" ");
		for(int i=0; i<j; i++) {
			if(matrix[post] == 1)
				printf("A ");
			else if (matrix[post] == 11)
				printf("J ");
			else if (matrix[post] == 12)
				printf("Q ");
			else if (matrix[post] == 13)
				printf("K ");
			else printf("%d ",matrix[post]);
			post++;
		}
		cout<<endl;
		cout<<endl;
	}
	for(int i=29; i<MAT_SIZE; i++) {
			if(matrix[i] == 1)
				printf("A ");
			else if (matrix[i] == 11)
				printf("J ");
			else if (matrix[i] == 12)
				printf("Q ");
			else if (matrix[i] == 13)
				printf("K ");
			else printf("%d ",matrix[i]);
		}
}

void generateCard(int *matrix)
{
	int number =1;
	for (int i =0 ; i < MAT_SIZE;i++)
	{
		if (number ==14) number =1;
		matrix[i] = number;
		number++;
	}
	
	random_shuffle(&matrix[0], &matrix[52]);
	random_shuffle(&matrix[0], &matrix[52], randomFunct);
	
}
int main()
{
	srand(unsigned(time(0)));
	// Declare Matrices

	int *matrix;
	matrix = (int *)malloc (MAT_SIZE * sizeof(int ));
	generateCard(matrix);
	printPyramid(matrix);

	return 0;
}