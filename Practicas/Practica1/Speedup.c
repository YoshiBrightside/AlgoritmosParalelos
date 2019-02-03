#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo de speedup para la practica 1.
* Mide cuántas veces más rápido es el algoritmo paralelo, a comparación del algoritmo secuencial.
* El valor ideal es n veces mayor, n siendo el número de procesos.
*
* Para compilar: gcc Speedup.c -o speedup.out -fopenmp
*/

int main(int argc, char** argv){
	
	// Nos aseguramos de que el usuario de los parametros requeridos
	if (argc < 4){
		printf("\nPor favor, especifique la velocidad secuencial, la velocidad paralela ");
		printf("y el número de procesadores.\n");
    	printf("Ejemplo de uso: ./speedup.out 4188587 1877365 4\n\n");
		exit(1);
	}

	int velocidad_secuencial, velocidad_paralela, procesadores;

	sscanf(argv[1], "%i", &velocidad_secuencial);
	sscanf(argv[2], "%i", &velocidad_paralela);
	sscanf(argv[3], "%i", &procesadores);

	printf("El speedup es de %f \n", (float)velocidad_secuencial/(velocidad_paralela/procesadores));
	exit(1);

}