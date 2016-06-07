#include <stdio.h>
#include "mpi.h"
#include <malloc.h>



int main(int argc,char *argv[]){
	

	int size, rank, dest, source, tag = 1;
	int max = 100;
	int arreglo[max];
	int *trozoarreglo;
	int i;
	int sumparcial = 0;
	int sumtotal = 0;
	

	MPI_Status Stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	int trozo = max / (size - 1);


	if (rank == 0) {


	  for(i = 1; i <= 100; i++) {
		arreglo[i - 1] = i;
	  }
	  
	  // Proceso 1
	  dest = 1;
	  MPI_Send(&arreglo[0], trozo, MPI_INT, dest, tag, MPI_COMM_WORLD);

	  // Proceso 2
	  dest = 2;
	  MPI_Send(&arreglo[trozo], trozo, MPI_INT, dest, tag, MPI_COMM_WORLD);

	  // Proceso 3
	  dest = 3;
	  MPI_Send(&arreglo[(trozo * 2)], trozo, MPI_INT, dest, tag, MPI_COMM_WORLD);

	  // Proceso 4
	  dest = 4;
	  MPI_Send(&arreglo[(trozo * 3)], trozo, MPI_INT, dest, tag, MPI_COMM_WORLD);
	  



	  // Proceso 1
	  source = 1;
	  MPI_Recv(&sumparcial, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  sumtotal += sumparcial;

	  // Proceso 2
	  source = 2;
	  MPI_Recv(&sumparcial, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  sumtotal += sumparcial;

	  // Proceso 3
	  source = 3;
	  MPI_Recv(&sumparcial, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  sumtotal += sumparcial;

	  // Proceso 4
	  source = 4;
	  MPI_Recv(&sumparcial, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  sumtotal += sumparcial;

	  printf("TOTAL = %d\n", sumtotal);


	} else if (rank == 1) {

	  // Proceso 0
	  dest = 0;
	  trozoarreglo = (int*)malloc(sizeof(int)*trozo);
	  MPI_Recv(trozoarreglo, trozo, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  int acumulador = 0;
	  for(i = 0; i < trozo; i++) {
		acumulador += trozoarreglo[i];
	  }
	  MPI_Send(&acumulador, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	} else if (rank == 2) {

	  // Proceso 0
	  dest = 0;
	  trozoarreglo = (int*)malloc(sizeof(int)*trozo);
	  MPI_Recv(trozoarreglo, trozo, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  int acumulador = 0;
	  for(i = 0; i < trozo; i++) {
		acumulador += trozoarreglo[i];
	  }
	  MPI_Send(&acumulador, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	} else if (rank == 3) {

	  // Proceso 0
	  dest = 0;
	  trozoarreglo = (int*)malloc(sizeof(int)*trozo);
	  MPI_Recv(trozoarreglo, trozo, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  int acumulador = 0;
	  for(i = 0; i < trozo; i++) {
		acumulador += trozoarreglo[i];
	  }
	  MPI_Send(&acumulador, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	} else if (rank == 4) {

	  // Proceso 0
	  dest = 0;
	  trozoarreglo = (int*)malloc(sizeof(int)*trozo);
	  MPI_Recv(trozoarreglo, trozo, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
	  int acumulador = 0;
	  for(i = 0; i < trozo; i++) {
		acumulador += trozoarreglo[i];
	  }
	  MPI_Send(&acumulador, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

	}


	MPI_Finalize();
}

