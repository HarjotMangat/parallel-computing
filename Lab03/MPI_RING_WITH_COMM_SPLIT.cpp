// Harjot Mangat
// EECS 245 - Parallel Computing
// Lab 03 - MPI
// This program implements the blocking send/recv calls for a ring of processes with communicator splitting.
//

#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#define  MASTER		0

int main(int argc, char* argv[])
{
	int   Global_numtasks, numtasks, World_taskid, taskid, message;
	double start, end;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &Global_numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &World_taskid);
	
	MPI_Barrier(MPI_COMM_WORLD);
	start = MPI_Wtime();
	//printf("Hello from task %d! \n", World_taskid);

	int color, key;
	char comm;
	if (World_taskid % 2 == 0) {
		color = 0;
		key = World_taskid;
		comm = 'A';
	}
	else {
		color = 1;
		key = World_taskid;
		comm = 'B';
	}
	MPI_Comm new_comm;
	MPI_Comm_split(MPI_COMM_WORLD, color,key, &new_comm);

	MPI_Comm_size(new_comm, &numtasks);
	MPI_Comm_rank(new_comm, &taskid);

	if (taskid == MASTER) {
		message = taskid;
		MPI_Send(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, new_comm);
		MPI_Recv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, new_comm, &status);
		printf("Message was %d \n", message);
	}
	else {
		MPI_Recv(&message, 1, MPI_INT, (taskid - 1 + numtasks) % numtasks, 1, new_comm, &status);

		printf("Task %d in comm %c has message %d \n", taskid, comm, message);
		message += 1;
		MPI_Send(&message, 1, MPI_INT, (taskid + 1) % numtasks, 1, new_comm);


	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	end = MPI_Wtime();
	MPI_Finalize();

	if (World_taskid == 0) {
			printf("elasped time was %f seconds\n", end - start); 
		}
}