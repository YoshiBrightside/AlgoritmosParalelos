#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>

/*
* Codigo para la practica 3.
* Realiza la aproximacion en el intervalo [3,17] de la siguiente funcion:
* 100 − (x − 10)4 + 50(x − 10)2 − 8x
*
* Para compilar: gcc Practica03.c -o practica03.out -fopenmp
*/

int main(int argc, char** argv){
	
	int MAX_HILOS=100; //limite superior del numero de hilos
	int numHilos, idHilo; 
	
	//verifica el numero de argumentos que recibe
	if (argc < 2){
		printf("por favor especifique el numero de procesadores\n");
		printf("ejemplo de uso: ./<programa> 4\n");
		exit(1);
	}
	//verifica el numero de hilos que recibe
	sscanf(argv[1], "%i", &numHilos);
	if (numHilos < 2 || numHilos > MAX_HILOS){
		printf("Numero de hilos no valido (%i). El numero maximo es de 100.\n", numHilos);
		exit(1);
	}

	//crea el numero de hilos necesarios, indices y agrega los elementos ingresados a un arreglo
	omp_set_num_threads(numHilos);
    double ancho = 14/(5*numHilos);
    double area_total = 0;
    double area_rectangulo = 0;
    double punto_x;
    double punto_y;

	//inicia seccion paralela
	#pragma omp parallel private(idHilo,area_rectangulo,ancho)
	{
        //obtenemos el área a trabajar de cada hilo
		idHilo = omp_get_thread_num();
        int i;
        for (i=0;i<5;i++){
            printf("Iteracion numero %i del procesador %i\n", i,idHilo);
            punto_x = ((double)(i+idHilo*5))*ancho;
            printf("idHilo: %i, X: %d \n",idHilo, punto_x);
            punto_y = 100-pow(punto_x-10,4.0)+50*pow(punto_x-10,2.0)-8.0*punto_x;
            //printf("Y: %d\n",pow(punto_x-10,4.0));
            //printf("Procesador %i, punto y %d, area total %d\n",idHilo,punto_y,area_total);
            area_rectangulo = punto_y*ancho;
            area_total += area_rectangulo;
        }
	} //fin de seccion paralela

    printf("Area total: %d\n", area_total);
	//imprime el resultado
}
