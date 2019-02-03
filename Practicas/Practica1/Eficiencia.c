#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
* Codigo de eficiencia para la practica 1.
* Mide que tan eficiententemente se usan los procesadores a comparacion del proceso secuencial.
* El valor ideal es 1.
*
* Para compilar: gcc Eficiencia.c -o eficiencia.out -fopenmp
*/

int main(int argc, char** argv){

    // Nos aseguramos de que el usuario de los parametros requeridos
	if (argc < 3){
		printf("\nPor favor, especifique el speedup y el numero de procesadores\n");
    	printf("Ejemplo de uso: ./eficiencia.out 2.231099 4\n\n");
		exit(1);
	}

    float speedup;
    int procesadores;
    sscanf(argv[1], "%f", &speedup);
    sscanf(argv[2], "%i", &procesadores);
    printf("La eficiencia de tus %i procesadores es de %f por procesador\n",procesadores, speedup/procesadores);
}