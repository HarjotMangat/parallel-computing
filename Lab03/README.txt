========================================
* Harjot Mangat                        *
* EECS 245 - Parallel Computing        *
* Lab 03                               *
========================================


***************************
*****MPI_BROADCAST.cpp*****
***************************
This program uses MPI to have one process compute some value and broadcast it to all other processes. This program uses the following include definitions:
	'iostream'
	'mpi.h'
	'stdlib.h'

I used MSMPI to run this program on a single machine.

******************************
****MPI_RING_BLOCKING.cpp*****
******************************
Implementation of a ring of processes passing values to the process on their right, uses blocking send/recv. It has the following include definitions:
	'mpi.h'
	'stdlib.h'
	'iostream'

I used MSMPI to run this program on a single machine.

*********************************
****MPI_RING_NON_BLOCKING.cpp****
*********************************
Implementation of a ring of processes passing values to the process on their right, uses non-blocking Isend/Irecv. It has the following include definitions:
	'mpi.h'
	'stdlib.h'
	'iostream'

I used MSMPI to run this program on a single machine.

************************************
****MPI_RING_WITH_COMM_SPLIT.cpp****
************************************
Implementation of a  ring of processes passing values to the process on their right, splits the world_comm into two sub communicators. It has the following include definitions:
	'mpi.h'
	'stdlib.h'
	'iostream'

I used MSMPI to run this program on a single machine.

******************************
****MPI_SCATTER_GATHER.cpp****
******************************
This program uses MPI to have one process initialize an array and send chunks of it to each process. The individual processes edit the array and send it back. Uses scatter & gather. It has the following include definitions:
	'mpi.h'
	'stdlib.h'
	'iostream'

I used MSMPI to run this program on a single machine.
