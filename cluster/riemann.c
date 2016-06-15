#include <stdio.h>
#include <mpi.h>
#include <math.h>

/*
* Archivo: riemann.c
*
* Makefile:
*	work2: riemann
*		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/work2
*	riemann:
*		mpicc riemann.c -o /shared/work2
* 
* Este programa en MPI realiza el calculo de la integral de una funcion mediante
* el metodo de sumas de Riemann para calcular el area bajo de curva de una funcion.
* 
* El calculo se hace para la funcion f(x) en el intervalo [-1, 1]
* 
* f(x) = x^2
*
* EL intervalo [-1, 1] se particiona en sub-intervalos correspondientes al
* numero de procesos que van a correr en MPI.
*
* gcc /vagrant/riemann.c -o riemann -lm
*
*/


#define LOWLIM -1.0
#define UPLIM 1.0
#define SIZEI 100

/*
* Funcion: f(x) = x^2
*/
float fx(float x)
{
	return pow(x , 2);
}


/*
* Punto medio entre dos valores
*/
float puntoMedio(float a, float b)
{
	return (a + b) / 2;
}


/*
* Area de un rectangulo
*/
float areaRectangulo(float altura, float base)
{
	return altura * base;
}


/*
* Delta entre dos valores
*/
float valorDelta(float a, float b)
{
	return b - a;
}


/*
* Imprime el intervalo creado
*/
void printIntervalo(float *intervalo)
{
	int i;
	for(i = 0; i < SIZEI; i++)
	{
		printf("[%d] = %f\n", i, intervalo[i]);
	}
}


int main(int argc, char** argv) {
	
	int i;
	// Intervalo de numeros reales donde se evalua la funcion
	float intervalo[SIZEI];
	// Fraccion para dividir el intervalo
	float fraccion1 = (LOWLIM / (SIZEI/2));
	float fraccion2 = (UPLIM / (SIZEI/2));
	// Creacion del intervalo
	for(i = 1; i <= SIZEI; i++)
	{
		if(i < SIZEI/2)
		{
			intervalo[i-1] = ((SIZEI/2) - (i-1)) * fraccion1;
		}
		if(i > SIZEI/2)
		{
			intervalo[i-1] = (i - (SIZEI/2)) * fraccion2;
		}
	}
	// Imprime el invervalo
	//printIntervalo(intervalo);
	
	
	
	int rank;
	int numtasks;
	int stride;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// El tamanio de cada sub-intervalo
	stride = SIZEI/(numtasks);
	
	// Sub-intervalo
	float subintervalo[stride];
	// Cuantos datos se envian en el buffer
	int sendcount[stride];
	// Cuanto es el desplazamiento relatizo al buffer que se envia, apartir del cual toma valores el proceso i
	int disp[stride];
	// Suma Total de Riemann
	float sumriemann[1] = {0.0};
	
	
	// Inicializa el desplazamiento y numero de datos relativo al buffer que se envia
	for(i = 0; i < numtasks; i++) {
		disp[i] = i * stride;
		sendcount[i] = stride;
	}
	
	
	// Comunicacion mediante el metodo MPI_Scatterv
	MPI_Scatterv(intervalo, sendcount, disp, MPI_FLOAT, subintervalo, stride, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	
	// Suma parcial para cada sub-intervalo
	float sumparcial = 0;
	// Valor inicial del subintervalo
	float a = subintervalo[0];
	// Valor final del subintervalo
	float b = subintervalo[stride - 1];
	// Punto medio del subintervalo
	float pm = puntoMedio(a, b);
	// Delta
	float delta = valorDelta(a, b);
	// Valor de la funcion
	float y = fx(pm);
	// Suma parcial
	sumparcial = areaRectangulo(y, delta);
	
	// Imprime la suma parcial
	printf("Suma Parcial %f en nodo %d\n", sumparcial, rank);
	
	
	// Aplica calculo de reduccion sumando los resultados parciales
	MPI_Reduce(&sumparcial, sumriemann, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	
	// Cuanto la suma de Riemann es completada
	if(rank == 0) {
		printf("Suma de Riemann: %f\n", sumriemann[0]);
	}
	

	MPI_Finalize();
	
	
	return 0;
}
