#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

/*
* Codigo que muestra la suma de los elementos de un vector usando MPI.
* Lo que hace la aplicación es partir en subvectores el vector original y cada subvector
* se envía a un nodo de procesamiento.
*/

#define MAX 100

int main(int argc, char** argv) {
    	int rank, size, i;
    	int vector[MAX], *miparte, stride;
    	int data;
    	int dest;
    	int source;
    	int tag = 1;
    	MPI_Status stat;

    	for (i = 1; i <= 100; i++)
            	vector[ i - 1 ] = i;
    	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    	stride = MAX/(size - 1);
    	if (rank == 0) {
            	int acum;
            	for (i = 1; i < size; i++)
                    	MPI_Send(&vector[stride*(i - 1)],stride,MPI_INT, i, tag, MPI_COMM_WORLD);
            	for (i = 1, acum = 0; i < size; i++) {
                    	int data;
                    	MPI_Recv(&data, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &stat);
                    	acum += data;
            	}
            	printf("Total %d\n",acum);
    	} else {
            	int acum = 0;
            	miparte = (int*)malloc(sizeof(int)*stride);
            	MPI_Recv(miparte, stride, MPI_INT, 0, tag, MPI_COMM_WORLD, &stat);
            	for (i = 0, acum = 0; i < stride; i++)
                    	acum += miparte[i];
            	MPI_Send(&acum, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    	}
    	MPI_Finalize();
}
