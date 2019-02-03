#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
* Codigo de fraccion serial para la practica 1.
* Mide la parte del código que es inherentemente secuencial.
* El valor ideal es 0.
*
* Para compilar: gcc Fraccion_serial.c -o fraccion_serial.out -fopenmp
*/

int main(int argc, char** argv){

    // Nos aseguramos de que el usuario de los parametros requeridos
	if (argc < 3){
		printf("\nPor favor, especifique el speedup y el numero de procesadores\n");
    	printf("Ejemplo de uso: ./fraccion_serial.out 2.231099 4\n\n");
		exit(1);
	}

    float speedup;
    int procesadores;
    sscanf(argv[1], "%f", &speedup);
    sscanf(argv[2], "%i", &procesadores);
    printf("El %f del codigo",((1/speedup)-(1/procesadores))/(1-(1/procesadores)));
    printf(" es inherentemente secuencial\n");
}