#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
* Codigo auxiliar para la practica 1.
* Realiza la suma de los primeros 1,000,000,000 numeros naturales de forma paralela
* y lleva registro del tiempo de ejecucion.
*
* Para Ejecutar: gcc Practica01.c -fopenmp
*/

int main(int argc, char** argv){
	struct timeval inicio, fin;//nos permiten medir el tiempo de ejecucion
	int tiempo;
	int tiempo_promedio;
	
	int MAX_HILOS=100; //limite superior (arbitrario) del numero de hilos
	int numHilos, idHilo;
	int procesos[] = {1,2,4,6,8,10,20,50,100};

/*	
*	//verifica el numero de hilos que se paso como parametro
*	if (argc < 2){
*		printf("por favor especifique el numero de hilos\n");
*		exit(1);
*	}
*	sscanf(argv[1], "%i", &numHilos);
*	if (numHilos < 1 || numHilos > MAX_HILOS){
*		printf("Numero de hilos no valido (%i)\n", numHilos);
*		exit(1);
*	}
*/

	int j;
	int k;
	//No hay un método length en C, por lo que debemos dividir el tamaño del arreglo entre el tamaño
	//de un espacio en dicho arreglo
	for(j=0;j<(sizeof(procesos)/sizeof(procesos[0]));j++) { 
		numHilos = procesos[j];
		tiempo_promedio = 0;

		omp_set_num_threads(numHilos);

		// Para evitar anomalias, se obtiene un promedio de ejecutar 10 veces la misma cantidad de hilos
		for(k=0;k<10;k++) {
			
			gettimeofday(&inicio, NULL);//guarda el tiempo al inicio del programa
			long int suma, sumaHilo;
			suma=0;

			//inicia seccion paralela
			#pragma omp parallel private(idHilo, sumaHilo)
    		{
				idHilo = omp_get_thread_num();
				if (idHilo==0){
					printf ("iniciando calculo con %i hilos\n", omp_get_num_threads());
				}

				//cada hilo realiza una suma parcial
				sumaHilo=0;
				int i;
				for (i=idHilo;i<1000000000;i+=numHilos){
					sumaHilo+=i;
				}

				//cada hilo actualiza la suma total con su resultado parcial
				suma+=sumaHilo;
			}//fin de seccion paralela

			gettimeofday(&fin, NULL); //guarda el tiempo al final del programa
			tiempo = (fin.tv_sec - inicio.tv_sec)* 1000000 + (fin.tv_usec - inicio.tv_usec);
			tiempo_promedio += tiempo;
			printf("suma: %li  \ntiempo de ejecucion: %i microsegundos\n",suma, tiempo);
		}
		printf("tiempo de ejecucion promedio: %i microsegundos\n",tiempo_promedio/10);
	}
		printf("procesadores en esta PC: %i \n", omp_get_num_procs());
}
