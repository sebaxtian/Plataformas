#include <mpi.h>
#include <stdio.h>

/*
* Codigo que muestra la interaccion del tipo token ring entre nodos de una aplicacion basada en MPI.
* Este ejemplo suma 1 a un dato desde el nodo 1 hasta el nodo 4 y el resultado total lo muestra el
* nodo 1.
*/

int main(int argc, char** argv) {
    	int rank, size;
    	int data;
    	int dest;
    	int source;
    	int tag = 1;
    	MPI_Status stat;

    	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	if (rank == 0) {
            	data = 1;
            	dest = rank + 1;
            	source = size - 1;
            	MPI_Send(&data, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
            	MPI_Recv(&data, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
            	printf("TOTAL: %d\n", data);
    	} else {
            	source = rank - 1;
            	dest = (rank + 1)%size;
            	MPI_Recv(&data, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
            	data = data + 1;
            	MPI_Send(&data, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    	}
    	MPI_Finalize();
}
