// Harjot Mangat
// EECS 245 - Parallel Computing
// Lab 03 - MPI
// This program implements the collective communication scatter/gather
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#define  MASTER		0
#define ARRAYSIZE 24

int main(int argc, char* argv[])
{
	int numtasks, taskid;
	int message[ARRAYSIZE];
	double start, end;


	MPI_Init(&argc, &argv);
	//start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);

	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	int *index = (int *)malloc(sizeof(int) * (ARRAYSIZE/numtasks));
	//printf("Hello from task %d! \n", taskid);
	if (taskid == MASTER) {
		for (int i = 0; i < ARRAYSIZE; i++) {
			message[i] = i;
		}
		printf("Proc %d initialized: \n[", taskid);
		for (int i = 0; i < ARRAYSIZE; i++) printf("%d ", message[i]);
		printf("]\n");
	}

	MPI_Scatter(message, ARRAYSIZE / numtasks, MPI_INT, 
				index, ARRAYSIZE / numtasks, MPI_INT,
				MASTER, MPI_COMM_WORLD);
	printf("Proc %d has initial data\n[", taskid);
	for (int i = 0; i < ARRAYSIZE / numtasks; i++) printf("%d ", index[i]);
	printf("]\n");

	for (int i = 0; i < ARRAYSIZE / numtasks; i++) {
		index[i] = index[i] + taskid;
	}
	printf("Proc %d has changed the values: \n[", taskid);
	for (int i = 0; i < ARRAYSIZE / numtasks; i++) printf("%d ", index[i]);
	printf("]\n");

	MPI_Gather(index, ARRAYSIZE / numtasks, MPI_INT,
				message, ARRAYSIZE / numtasks, MPI_INT,
				MASTER, MPI_COMM_WORLD);
	if (taskid == MASTER) {
		printf("Proc %d has the returned array of: \n[", taskid);
		for (int i = 0; i < ARRAYSIZE; i++) printf("%d ", message[i]);
		printf("]\n");
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	
	MPI_Finalize();
	if (taskid == 0) {
			printf("elasped time was %f seconds\n", end - start); 
		}
}