#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo para la practica 6.
* Obtiene un máximo elemento en un arreglo.
*
* Para compilar: gcc Practica06.c -o practica06.out -fopenmp
*/

int main(int argc, char** argv){

    int MAX_HILOS=100; //limite superior del numero de hilos
	int numHilos, idHilo, vertices, semilla; 
	
	//verifica el numero de argumentos que recibe
	if (argc < 2){
		printf("Por favor especifique el numero elementos y la semilla generadora\n");
		printf("ejemplo de uso: ./<programa> 8 1234\n");
		exit(1);
	}
	//verifica el numero de hilos que recibe
	sscanf(argv[1], "%i", &numHilos);
	vertices = numHilos;
	if (numHilos < 0 || numHilos > MAX_HILOS){
		printf("Numero de hilos (vertices) no valido (%i). El numero maximo es de 100.\n", numHilos);
		exit(1);
	}
	//verifica que el numero de elementos que reciba corresponda
	sscanf(argv[2], "%i", &semilla);
	if (semilla < 0){
		printf("Semilla no valida (%i).\n", numHilos);
		exit(1);
	}

	

}