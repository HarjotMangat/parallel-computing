// Harjot Mangat
// EECS 245 - Parallel Computing
// Lab 03 - MPI
// This program implements the collective communication broadcast feature
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#define  MASTER		0

int main(int argc, char* argv[])
{
	int   numtasks, taskid;
	double message;
	double start, end;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	//start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	//printf("Hello from task %d! \n", taskid);
	if (taskid == MASTER) {
		message = 16;
		message = sqrt(message);
		printf("message is %lf.", message);
	}
	MPI_Bcast(&message, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
	if (taskid != MASTER) {
		printf("task %d got message %lf \n", taskid, message);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	
	MPI_Finalize();
	if(taskid==0){
		printf("\nelasped time was %f seconds", end - start);
		}
}