#include <mpi.h>
#include <stdio.h>

/*
* Ejemplo de uso de MPI_Scatterv
*/

#define SIZE 4

main(int argc, char *argv[])  {
    	
	int numtasks;
	int rank;
	int source = 0;
	int dest;
	int tag = 1;
	int i;
	
	float a[SIZE * SIZE] = {1.0, 2.0, 3.0, 4.0,
							5.0, 6.0, 7.0, 8.0,
							9.0, 10.0, 11.0, 12.0,
							13.0, 14.0, 15.0, 16.0};
	
	float b[SIZE];
	float acum;
	int disp[SIZE];
	int scounts[SIZE];
	
	//MPI_Status stat;
	//MPI_Datatype rowtype;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	for (i = 0; i < numtasks; i++) {
		disp[i] = i * SIZE;
		scounts[i] = SIZE;
	}
	
	MPI_Scatterv(a, scounts, disp, MPI_FLOAT, b, SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	acum = 0.0;
	for (i = 0; i < SIZE; i++)
		acum += b[i];
	
	printf("Subtotal %lf en nodo %d\n", acum, rank);
	
	MPI_Reduce(&acum, b, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (rank == 0)
		printf("TOTAL: %lf\n", b[0]);
	
	MPI_Finalize();
}
