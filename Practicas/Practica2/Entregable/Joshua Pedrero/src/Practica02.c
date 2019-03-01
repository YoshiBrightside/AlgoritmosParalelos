#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo para la practica 2.
* Realiza el ordenamiento de un arreglo de forma paralela
*
* Para compilar: gcc Practica02.c -o practica02.out -fopenmp
*/

int main(int argc, char** argv){
	
	int MAX_HILOS=100; //limite superior del numero de hilos
	int numHilos, idHilo; 
	
	//verifica el numero de argumentos que recibe
	if (argc < 2){
		printf("por favor especifique el numero de elementos a ordenar, y dichos elementos\n");
		printf("ejemplo de uso: ./<programa> 4 3 2 4 1\n");
		exit(1);
	}
	//verifica el numero de hilos que recibe
	sscanf(argv[1], "%i", &numHilos);
	if (numHilos < 2 || numHilos > MAX_HILOS){
		printf("Numero de hilos no valido (%i). El numero maximo es de 100.\n", numHilos);
		exit(1);
	}
	//verifica que el numero de elementos que reciba corresponda
	if (argc < 2+numHilos){
		printf("el numero de elementos no corresponde al numero de elementos ingresados\n");
		printf("ejemplo de uso: ./<programa> 4 3 2 4 1\n");
		exit(1);
	}

	//crea el numero de hilos necesarios, indices y agrega los elementos ingresados a un arreglo
	omp_set_num_threads(numHilos);
	int i, j, k, aux;
	int arreglo[numHilos];
	for (i = 2; i <= numHilos+1; i++) {
		sscanf(argv[i], "%i", &arreglo[i-2]);
	}

/*
	//imprime el arreglo
	for (i = 0; i < (sizeof(arreglo)/sizeof(arreglo[0])); i++) {
		printf("arr %i: %i \n", i, arreglo[i]);
	}
*/


	//No hay un método length en C, por lo que debemos dividir el tamaño del arreglo entre el tamaño
	//de un espacio en dicho arreglo.
	for(k=0; k<((sizeof(arreglo)/sizeof(arreglo[0]))); k++) {
		
		//inicia seccion paralela
		#pragma omp parallel private(idHilo)
   		{
			idHilo = omp_get_thread_num();

			//Paso impar
			//notese que el paso 0 es el primer paso, y por ende, el paso impar
			if (idHilo%2==0 && k%2==0){
				if((idHilo+1 < ((sizeof(arreglo)/sizeof(arreglo[0])))) &&
					arreglo[idHilo] > arreglo[idHilo+1]) {
					aux = arreglo[idHilo];
					arreglo[idHilo] = arreglo[idHilo+1];
					arreglo[idHilo+1] = aux;
				}
			}

			//Paso impar
			//notese que el paso 1 es el segundo paso, y por ende, el paso par
			if (idHilo%2==1 && k%2==1){
				if((idHilo+1 < ((sizeof(arreglo)/sizeof(arreglo[0])))) &&
					arreglo[idHilo] > arreglo[idHilo+1]) {
					aux = arreglo[idHilo];
					arreglo[idHilo] = arreglo[idHilo+1];
					arreglo[idHilo+1] = aux;
				}
			}
		
		} //fin de seccion paralela
	}

	//imprime el arreglo, ya ordenado y chido
	for (i = 0; i < (sizeof(arreglo)/sizeof(arreglo[0])); i++) {
		printf("arr %i: %i \n", i, arreglo[i]);
	}
}
