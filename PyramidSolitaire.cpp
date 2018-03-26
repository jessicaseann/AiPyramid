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

bool covered(int *matrix,int *row, int pair)
{
	if(row[pair]==7) return false;
	else if(matrix[row[pair]+pair]!=0 || matrix[row[pair]+pair+1]!=0 ) return true; //Card covered
	else return false;
}

void pairCard(int *matrix, int row[], int pair1, int pair2)
{
	if(matrix[pair1]+matrix[pair2]==13 && !covered(matrix, row, pair1) && !covered(matrix, row, pair2)){
		matrix[pair1]=0;
		matrix[pair2]=0;
	}
}

void pairCard(int *matrix, int row[], int pair1)
{
	if(matrix[pair1] && !covered(matrix, row, pair1)){
		matrix[pair1]=0;
	}
}


void printPyramid(int *matrix, int row[])
{	
	system("cls");
	// End of Declaration
	int post =0;
	for (int j =0 ; j<=7;j++)
	{
		for (int m=6-j ; m>=0;m--) printf("  ");
		for(int i=0; i<j; i++) {
			if(matrix[post] == 1)
				printf("A   ");
			else if (matrix[post] == 10)
				printf("10  ");
			else if (matrix[post] == 11)
				printf("J   ");
			else if (matrix[post] == 12)
				printf("Q   ");
			else if (matrix[post] == 13)
				printf("K  ");
			else printf("%d   ",matrix[post]);
			post++;
		}
		cout<<endl;
		cout<<endl;
	}
	
	cout<<endl;
	
	for(int i=post;i<MAT_SIZE; i++) {
			if(row[i] == 8) 
				printf("*  ");
			else if(matrix[i] == 1)
				printf("A ");
			else if (matrix[i] == 11)
				printf("J ");
			else if (matrix[i] == 12)
				printf("Q ");
			else if (matrix[i] == 13)
				printf("K  ");
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
	
	int row[52] = { 1,
					2, 2,
					3, 3, 3,
					4, 4, 4, 4,
					5, 5, 5, 5, 5,
					6, 6, 6, 6, 6, 6, 
					7, 7, 7, 7, 7, 7, 7,
					9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
					};

	int *matrix;
	matrix = (int *)malloc (MAT_SIZE * sizeof(int ));
	generateCard(matrix);
	printPyramid(matrix, row);
	int a,b;
	cin>>a>>b;
	pairCard(matrix, row, a, b);
	printPyramid(matrix,row);

	return 0;
}
