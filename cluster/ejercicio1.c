#include <stdio.h>
#include "mpi.h"



int main(int argc,char *argv[]){
	
	int size, rank, dest, source, count, tag=1;
	int invalue, outvalue = 1;
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = 3;

	  MPI_Send(&outvalue, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
	  MPI_Recv(&invalue, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);

	  printf("TOTAL = %d\n", invalue);

	} else if (rank == 1) {
	  source = 0;
	  dest = 2;

	  MPI_Recv(&invalue, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  outvalue = invalue + 1;
	  MPI_Send(&outvalue, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	} else if (rank == 2) {
	  source = 1;
	  dest = 3;

	  MPI_Recv(&invalue, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  outvalue = invalue + 1;
	  MPI_Send(&outvalue, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	} else if (rank == 3) {
	  source = 2;
	  dest = 0;

	  MPI_Recv(&invalue, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  outvalue = invalue + 1;
	  MPI_Send(&outvalue, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	}
	
	
	printf("Rank [%d] TOTAL = %d\n", rank, invalue);


	MPI_Finalize();
}

