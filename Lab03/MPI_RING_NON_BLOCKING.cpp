// Harjot Mangat
// EECS 245 - Parallel Computing
// Lab 03 - MPI
// This program implements the non-blocking Isend/Irecv calls for a ring of processes
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#define  MASTER		0

int main(int argc, char* argv[])
{
	int   numtasks, taskid, message, wait_count;
	double start, end;
	MPI_Status status;
	MPI_Request send_request;
	MPI_Request recv_request;

	MPI_Init(&argc, &argv);
	//start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	
	printf("Hello from task %d! \n", taskid);
	if (taskid == MASTER) {
		message = taskid;
		MPI_Isend(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, MPI_COMM_WORLD, &send_request);
		MPI_Irecv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, MPI_COMM_WORLD, &recv_request);
		int flag = 0;
		wait_count = 0;
		do {
			wait_count++;
			MPI_Test(&recv_request, &flag, &status);
		} while (!flag);

		printf("Message was %d . After waiting %d times.\n", message, wait_count);
	}
	else {
		MPI_Irecv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, MPI_COMM_WORLD, &recv_request);
		int flag = 0;
		wait_count = 0;
		do {
			wait_count++;
			MPI_Test(&recv_request, &flag, &status);
		} while (!flag);

		printf("Task %d has message %d . After waiting %d times. \n", taskid, message, wait_count);

		message += 1;
		MPI_Isend(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, MPI_COMM_WORLD, &send_request);


	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	MPI_Finalize();
	
	if (taskid == 0) {
			printf("elasped time was %f seconds\n", end - start); 
		}

}