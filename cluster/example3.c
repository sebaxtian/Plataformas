#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>

/*
* Archivo: example3.c
*
* Makefile:
*	ex3: example3
*		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 5 --hostfile /shared/machinefile /shared/ex3
*	example3:
*		mpicc example3.c -o /shared/ex3
*
* Este codigo es similar al example2.c solo que se introdujo la funcion
* MPI_Reduce y se eliminaron lineas en C que hacian la tarea de MPI_Reduce.
*
*/

#define MAX 100

int main(int argc, char** argv) {
	
		// Establece el tiempo inicial del programa
		clock_t t_start = clock();
	
    	int rank, size, i;
    	int vector[MAX], *miparte, stride;
    	int data;
    	int dest;
    	int source;
    	int tag = 1;
    	int acum = 0;
    	int total = 0;
    	MPI_Status stat;

    	for (i = 1; i <= 100; i++)
            	vector[ i - 1 ] = i;
	
    	MPI_Init(&argc,&argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size);
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
    	stride = MAX/(size - 1);
	
    	if (rank == 0) {
            	for (i = 1; i < size; i++)
                    	MPI_Send(&vector[stride*(i - 1)],stride,MPI_INT, i, tag, MPI_COMM_WORLD);
    	} else {
            	acum = 0;
            	miparte = (int*)malloc(sizeof(int)*stride);
            	MPI_Recv(miparte, stride, MPI_INT, 0, tag, MPI_COMM_WORLD, &stat);
            	for (i = 0, acum = 0; i < stride; i++)
                    	acum += miparte[i];
    	}
	
    	MPI_Reduce(&acum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
    	if (rank == 0) {
            	printf("Total: %d\n", total);
				// Establece el tiempo final del programa
				clock_t t_end = clock();
				// Tiempo de ejecucion del programa
				clock_t t_run = t_end - t_start;
				printf ("Tiempo de Ejecucion: (%f segundos).\n",((float)t_run)/CLOCKS_PER_SEC);
		}
	
    	MPI_Finalize();
	
		return 0;
}
