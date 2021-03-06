#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo de speedup para la practica 1.
* Mide cuantas veces mas rapido es el algoritmo paralelo, a comparacion del algoritmo secuencial.
* El valor ideal es n veces mayor, n siendo el numero de procesos.
*
* Para compilar: gcc Speedup.c -o speedup.out -fopenmp
*/

int main(int argc, char** argv){
	
	// Nos aseguramos de que el usuario de los parametros requeridos
	if (argc < 4){
		printf("\nPor favor, especifique la velocidad secuencial, la velocidad paralela ");
		printf("y el numero de procesadores.\n");
    	printf("Ejemplo de uso: ./speedup.out 4188587 1877365 4\n\n");
		exit(1);
	}

	float velocidad_secuencial, velocidad_paralela;
	int procesadores;

	sscanf(argv[1], "%f", &velocidad_secuencial);
	sscanf(argv[2], "%f", &velocidad_paralela);
	sscanf(argv[3], "%i", &procesadores);

	printf("El speedup es de %f para %i procesadores\n", velocidad_secuencial/velocidad_paralela, procesadores);
	exit(1);

}