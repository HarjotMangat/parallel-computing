/* Harjot Mangat
* EECS 245 - Parallel Computing
* Lab 04
* C program to solve N Queen Problem using backtracking and Cilk+ */

// The sequential version of this code is contributed by Aditya Kumar (adityakumar129)
// Edited wtih Cilk implementation by Harjot Mangat

#define N 4  //Adjust this value for number of queens
#include <stdbool.h>
#include <stdio.h>

#include <cilk/cilk.h>
#include <iostream>

/* A utility function to print solution */
void printSolution(int board[N][N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf(" %d ", board[i][j]);
		printf("\n");
	}
}

/* A utility function to check if a queen can
be placed on board[row][col]. */
bool isSafe(int board[N][N], int row, int col)
{
	int i, j;

	for (i = 0; i < col; i++)
		if (board[row][i]) {
			//std::cout << "check left side " << board[row][i] << std::endl;
			return false;
		}

	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j]) {
			//std::cout << "check negative diagonal " << board[i][j] << std::endl;
			return false;
		}
	for (i = row, j = col; j >= 0 && i < N; i++, j--)
		if (board[i][j]) {
			//std::cout << "check positive diagonal " << board[i][j] << std::endl;
			return false;
		}

	return true;
}

/* A recursive utility function to solve N
Queen problem */
int solveNQUtil(int board[N][N], int col)
{
	/* base case: If all queens are placed
	then return true */
	if (col >= N) {
		//printf("Hit the base case\n");
		return 1;
	}

	/* Consider this column and try placing
	this queen in all rows one by one */
	for (int r = 0; r < N; r++) {
		/* Check if the queen can be placed on
		board[r][col] */
		if (isSafe(board, r, col)) {
			/* Place this queen in board[r][col] */
			board[r][col] = 1;

			/* recur to place rest of the queens */
			int returns = cilk_spawn solveNQUtil(board, col + 1);
			cilk_sync;
			if (returns == 1){
			//printf("exited??\n");
			return 1;
			}

			/* If placing queen in board[r][col]
			doesn't lead to a solution, then
			remove queen from board[r][col] */
			board[r][col] = 0; // BACKTRACK
			//printf("backtracked\n");
		}
	}

	/* If the queen cannot be placed in any row in
		this column col then return false */
	return 0;
}

/* This function initializes the board and prints placement of queens in the form of 1s. */
void solveNQ()
{
	int board[N][N] = { { 0, 0, 0, 0 },
						{ 0, 0, 0, 0 },
						{ 0, 0, 0, 0 },
						{ 0, 0, 0, 0 } };

	if (solveNQUtil(board, 0) == 0) {
		printf("Solution does not exist\n");
	}

	printSolution(board);
}

// driver program to test above function
int main()
{
	std::cout << "Using " << N << "Queens";
	solveNQ();
	return 0;
}

