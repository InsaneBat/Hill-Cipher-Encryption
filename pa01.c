/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill Cipher
|
| Author: Axel Alvarado
| Language: c
|
| To Compile: gcc -o pa01 pa01.c
|
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2023
| Instructor: McAlpin
| Due Date: March 6, 2023
|
+=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_COL 80

void convert_char(int n, int size_block, int c[][n], char c_char[][n]);
void convert_int(int n, int size_block, char block_output[][n], int block_int[][n]);
void output(char array[], int n, int mat[][n],int size_block, char c_char[][n]);
void matrix_mult(int n, int size_block, int mat[][n], int c[][n], int block_int[][n]);
void block(int n, char array[], int size_block, char block_output[][n]);

//-------------------------------------------------------------------------------------------------------
int main(int argc, char **argv )
{
    char array[10000] = {0};
	int matrix[100];
	int n;
	int matrix_size;

    char *kname = argv[1];
	char *fname = argv[2];
	FILE *key = fopen(kname, "r");
    FILE *file = fopen(fname, "r");

    if (key == NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
    else
    {
		
		int number;
		int x;

		fscanf(key, "%d", &n);
		while (fscanf(key, "%d", &number) == 1)
		{
			matrix[x] = number;
			x++;
			matrix_size++;
		}

        fclose(key);
    }

	int size = 0;
	if (file == NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
	else
	{
        
		char c; 
        int i = 0;
		
		while (fscanf(file, "%c", &c) != EOF)
		{
			if (isalpha(c))
			{
                array[i] = tolower(c);
				size++;
                i++;
			}
		}
		fclose(file);
	}

	for (int m = 0; m < (size % n); m++)
	{
		array[size++] = 'x';
	}

	int mat[100][n];
	int count = 0;
	for(int e = 0; e < n; e++)
	{
		for (int f = 0; f < n; f++)
		{
			mat[e][f] = matrix[count];
			count++;
		}
	}


	int size_block = strlen(array) / n;
	char block_output[size_block][n];
	int block_int[size_block][n];
	

	block(n, array, size_block, block_output);

	convert_int(n, size_block, block_output, block_int);

	int c[size_block][n];

	matrix_mult(n, size_block, mat, c, block_int);

	char c_char[size_block][n];

	convert_char(n, size_block, c, c_char);

	printf("\n");

    output(array, n, mat, size_block, c_char);

	printf("\n");
    
	
	return 0;
}

//-------------------------------------------------------------------------------------------------------
void convert_char(int n, int size_block, int c[][n], char c_char[][n])
{
	for (int i = 0; i < size_block; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c_char[i][j] = (char)c[i][j] + 97;
		}
	}
}

//-------------------------------------------------------------------------------------------------------
void convert_int(int n, int size_block, char block_output[][n], int block_int[][n])
{

	for (int i = 0; i < size_block; i++)
	{
		for (int j = 0; j < n; j++)
		{
			block_int[i][j] = (int)block_output[i][j] - 97;
		}
	}
}

//-------------------------------------------------------------------------------------------------------
void block(int n, char array[], int size_block, char block_output[][n])
{
	int x = 0;
	int counter;
	for (int i = 0; i < size_block; i++)
	{
		
		for (int j = 0; j < n; j++)
		{
			block_output[i][j] = array[x];
			x++;
			counter++;
		}
	}
}



//-------------------------------------------------------------------------------------------------------
void matrix_mult(int n, int size_block, int mat[][n], int c[][n], int block_int[][n])
{
	for (int i = 0; i < size_block; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j] = 0;
			for (int x = 0; x < n; x++)
			{
				c[i][j] += block_int[i][x] * mat[j][x];

				c[i][j] = c[i][j] % 26;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------
void output(char array[], int n, int mat[][n], int size_block, char c_char[][n])
{

	printf("Key matrix:\n");

	for (int i = 0; i < n; i++)
	{
		for (int x = 0; x < n; x++)
		{
			printf("  %2d", mat[i][x]);
		}
		printf("\n");
	}


		printf("\n");

    printf("Plaintext:");
    for (int j = 0; j < strlen(array); j++)
    {
		if(j % 80 == 0)
		{
			printf("\n");
		}
		printf("%c", array[j]);
    }

	printf("\n\n");
	printf("Ciphertext:");
	int count = 0;
	for (int e = 0; e < size_block; e++)
	{
		for (int y = 0; y < n; y++)
		{
			if(count % 80 == 0)
			{
				printf("\n");
			}
			printf("%c", c_char[e][y]);
			count++;
		}
	}

}

/*=============================================================================
| I Axel Alvarado (5098358) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/