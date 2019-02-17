#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo p la practica 2.
* Realiza el ordenamiento de un arreglo de forma paralela
*
* Para compilar: gcc Practica02.c -o practica02.out -fopenmp
*/


int main(int argc, char** argv){
	
	int MAX_HILOS=100; //limite superior (arbitrario) del numero de hilos
	int numHilos, idHilo;
	
	//verifica el numero de hilos que se paso como parametro
	if (argc < 2){
		printf("por favor especifique el numero de elementos a ordenar, y dichos elementos\n");
		exit(1);
	}

	sscanf(argv[1], "%i", &numHilos);
	if (numHilos < 2 || numHilos > MAX_HILOS){
		printf("Numero de hilos no valido (%i)\n", numHilos);
		exit(1);
	}
	omp_set_num_threads(numHilos);

	int i;
	int j;
	int k;
	int arreglo[numHilos];

	for (i = 2; i <= numHilos+1; i++) {
		sscanf(argv[i], "%i", &arreglo[i-2]);
	}

	for (i = 0; i < (sizeof(arreglo)/sizeof(arreglo[0])); i++) {
		printf("arr %i: %i \n", i, arreglo[i]);
	}

	//No hay un método length en C, por lo que debemos dividir el tamaño del arreglo entre el tamaño
	//de un espacio en dicho arreglo
	// Se hace en paralelo n/2 veces
	for(k=0; k<((sizeof(arreglo)/sizeof(arreglo[0]))); k++) {
		
		int aux;
		//inicia seccion paralela
		#pragma omp parallel private(idHilo)
   		{
			idHilo = omp_get_thread_num();
			if (idHilo%2==0 && k%2==0){
				printf("Medio se logro el paso impar\n");
				printf("%i \n", idHilo);
				printf("%i \n", arreglo[idHilo]);
				if((idHilo+1 < ((sizeof(arreglo)/sizeof(arreglo[0])))) &&
					arreglo[idHilo] > arreglo[idHilo+1]) {
					printf("Si se logro el paso impar\n");
					aux = arreglo[idHilo];
					arreglo[idHilo] = arreglo[idHilo+1];
					arreglo[idHilo+1] = aux;
				}
			}

			if (idHilo%2==1 && k%2==1){
				printf("Medio se logro el paso par\n");
				printf("%i \n", idHilo);
				printf("%i \n", arreglo[idHilo]);
				if((idHilo+1 < ((sizeof(arreglo)/sizeof(arreglo[0])))) &&
					arreglo[idHilo] < arreglo[idHilo+1]) {
					printf("Si se logro el paso par\n");
					aux = arreglo[idHilo];
					arreglo[idHilo] = arreglo[idHilo+1];
					arreglo[idHilo+1] = aux;
				}
			}

			//cada hilo realiza una suma parcial
/*			sumaHilo=0;
			int i;
			for (i=idHilo;i<1000000000;i+=numHilos){
				sumaHilo+=i;
			}
*/

			//cada hilo actualiza la suma total con su resultado parcial
		}//fin de seccion paralela

	}

	for (i = 0; i < (sizeof(arreglo)/sizeof(arreglo[0])); i++) {
		printf("arr %i: %i \n", i, arreglo[i]);
	}
}
