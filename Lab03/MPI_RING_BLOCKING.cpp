// Harjot Mangat
// EECS 245 - Parallel Computing
// Lab 03 - MPI
// This program implements the blocking send/recv calls for a ring of processes
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#define  MASTER		0

int main(int argc, char* argv[])
{
	int   numtasks, taskid, message;
	double start, end;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	//start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	printf("Hello from task %d! \n", taskid);
	if (taskid == MASTER) {
		message = taskid;
		MPI_Send(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, MPI_COMM_WORLD);
		MPI_Recv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, MPI_COMM_WORLD, &status);
		printf("Message was %d \n", message);
	}
	else {
		MPI_Recv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, MPI_COMM_WORLD, &status);

		printf("Task %d has message %d \n", taskid, message);
		message += 1;
		MPI_Send(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, MPI_COMM_WORLD);


	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	MPI_Finalize();
	
	if (taskid == 0) {
			printf("elasped time was %f seconds\n", end - start); 
		}

}