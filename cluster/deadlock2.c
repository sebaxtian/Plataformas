#include <stdio.h>
#include "mpi.h"


/*
* 
* Este programa es un ejemplo de abrazo mortal entre procesos
* usando la libreria MPI.
* 
* No presenta un Deadlock por que se esta haciendo un llamado desde dos procesos
* diferentes al mismo tiempo a la funcion MPI_Send() esta funcion envia un
* mensaje hacia el buffer del sistema y continua ejecutando las instrucciones
* siguientes.
*
* Como los dos procesos, uno identificado con rank = 0 y el otro identificado
* con rank = 1 tiene la misma instruccion inicial MPI_Send() entonces
* no hay evidencia de un evento Deadlock y la ejecucion del programa continua
* luego cada uno de los procesos reciben el mensaje haciendo el llamado
* a la funcion MPI_Recv().
* 
*/


int main(int argc,char *argv[]){
	int size, rank, dest, source, count, tag=1;
	char inmsg, outmsg='x';
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = 1;
	  MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	  MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
	}else if (rank == 1) {
	  dest = 0;
	  source = 0;
	  MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	  MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
	 }

	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n",
		   rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	MPI_Finalize();
}

