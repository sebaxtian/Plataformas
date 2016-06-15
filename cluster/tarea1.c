#include <mpi.h>
#include <stdio.h>
#include <time.h>

/*
* Archivo: tarea1.c
*
* Makefile:
*	work1: tarea1
*		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/work1
*	tarea1:
*		mpicc tarea1.c -o /shared/work1
* 
* Este codigo es similar al example2.c solo que se introdujo la funcion
* MPI_Reduce y se eliminaron lineas en C que hacian la tarea de MPI_Reduce.
* Se introduce la funcion MPI_Scatterv para eliminar las lineas de codigo
* que hacian la tarea de MPI_Send y MPI_Recv en example3.c
*
*/

#define MAX 100

int main(int argc, char** argv) {
	
	// Establece el tiempo inicial del programa
	clock_t t_start = clock();
	
	int rank;
	int numtasks;
	int i;
	int stride;
	
	int vector[MAX];
	
	for(i = 1; i <= 100; i++)
		vector[ i - 1 ] = i;
	

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	stride = MAX/(numtasks);
	//printf("Stride: %d\n", stride);
	
	int vtmp[stride];
	int disp[stride];
	int sendcount[stride];
	int acum;
	
	
	for(i = 0; i < numtasks; i++) {
		disp[i] = i * stride;
		sendcount[i] = stride;
	}
	
	// &vector: desde donde se van a tomar los datos
	// sendcount: cuantos datos voy a enviar
	// disp: cuanto es el desplazamiento relativo a sendbuff, apartir del cual toma valores el proceso i
	// sendtype: el tipo de dato que voy a enviar
	// &recvbuff: donde se van almacenar los datos
	// recvcount: cuantos datos va a recibir
	// recvtype: el tipo de dato que va a recibir
	// root: quien origina la distribucion de los datos
	// comm: comunicador de procesos
	// MPI_Scatterv(&sendbuff, sendcount, sendtype, &recvbuff, recvcount, recvtype, root, comm)
	
	MPI_Scatterv(vector, sendcount, disp, MPI_INT, vtmp, stride, MPI_INT, 0, MPI_COMM_WORLD);
	
	acum = 0;
	for(i = 0; i < stride; i++) {
		acum += vtmp[i];
	}
	
	printf("Subtotal %d en nodo %d\n", acum, rank);
	
	MPI_Reduce(&acum, vtmp, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("TOTAL: %d\n", vtmp[0]);
		// Establece el tiempo final del programa
		clock_t t_end = clock();
		// Tiempo de ejecucion del programa
		clock_t t_run = t_end - t_start;
		printf ("Tiempo de Ejecucion: (%f segundos).\n",((float)t_run)/CLOCKS_PER_SEC);
	}

	MPI_Finalize();
	
	
	return 0;
}
