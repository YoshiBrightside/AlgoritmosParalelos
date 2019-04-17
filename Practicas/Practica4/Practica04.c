#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#include <unistd.h>

/*
* Codigo para la practica 4.
* Realiza la suma de prefijos de 2^n elementos aleatorios,
* con 2^n =< 100
*
* Para compilar:gcc Practica04.c -lm -w -o practica04.out -fopenmp
*/


int main(int argc, char** argv){
	
	int MAX_HILOS=100; //limite superior del numero de hilos
	int numHilos, idHilo, semilla; 
	
	//verifica el numero de argumentos que recibe
	if (argc < 3){
		printf("por favor especifique la potencia de 2 para el arreglo, y la semilla generadora\n");
		printf("ejemplo de uso: ./<programa> 4 1234\n");
		exit(1);
	}
	//verifica el tamanio del arreglo
	sscanf(argv[1], "%i", &numHilos);
	if (numHilos < 0 || pow(2,numHilos) > MAX_HILOS){
		printf("Tamanio de arreglo no valido. La potencia maxima admitida es 6.\n");
		exit(1);
	}
    //verifica la semilla generadora
	sscanf(argv[1], "%i", &semilla);
	if (numHilos < 0){
		printf("Semilla generadora no valida.\n");
		exit(1);
	}

	//crea el numero de hilos necesarios y el arreglo a trabajar
    numHilos = pow(2,numHilos);
	omp_set_num_threads(numHilos);
	int len = numHilos;
	int altura_max = (int)sqrt(numHilos)+1;
	int arreglo_y[altura_max][len/2];
	int arreglo_z[altura_max][len/2];
    int i,k,aux;
	aux = 0;
    srand(semilla);
    for (i = 0; i < numHilos; i++) {
        arreglo_y[0][i] = i+1;//rand();
		printf("arr[0][%i]: %i\n", i, arreglo_y[0][i]);
    }

	// INICIA ALGORITMO -------------------------------------------------------
	// 1. Si el arreglo solo tiene un elemento, devuelve dicho arreglo.

	// 2. Asignamos valores de y

	printf("Inicia proceso de llenado de arbol Y\n");
	for (i = 1; i <= altura_max; i++) {
		#pragma omp parallel private(idHilo)
		{
			idHilo = omp_get_thread_num();
			if (idHilo < len/2) {
				arreglo_y[i][idHilo] = arreglo_y[i-1][(2 * idHilo)] + arreglo_y[i-1][(2 * idHilo)+1];
				printf("arr[%i][%i]: %i\n", i, idHilo, arreglo_y[i][idHilo]);
				//printf("de arr[%i][%i]: %i con ", i-1, 2 * idHilo, arreglo_y[i-1][2 * idHilo]);
				//printf("arr[%i][%i]: %i\n",i-1,2 * idHilo+1, arreglo_y[i-1][2 * idHilo+1]);
			}
		}
		len = len/2;
	}

	// 3. Asignamos valores de z
	printf("Inicia proceso de llenado de arbol Z\n");
	arreglo_z[altura_max-1][0] = arreglo_y[altura_max-1][0];
	for (i = altura_max-2; i >= 0; i--) {
		#pragma omp parallel private(idHilo)
		{
			idHilo = omp_get_thread_num();
			if (arreglo_y[i][idHilo] != 0) {
				if(idHilo == 0) {
					arreglo_z[i][idHilo] = arreglo_y[i][0];
				}
				if(idHilo%2==0) {
					arreglo_z[i][idHilo] = arreglo_z[i+1][idHilo/2];
				}
				if(idHilo%2==1 && idHilo != 0) {
					arreglo_z[i][idHilo] = arreglo_z[i+1][(idHilo-1)/2] + arreglo_y[0][idHilo]; 
				}
			}
		}
	}

	//imprime el resultado
	printf("Resultados:\n");
    for (i = 0; i < numHilos; i++) {
        printf("arr[%i]: %i\n", i, arreglo_z[0][i]);
    }
}
