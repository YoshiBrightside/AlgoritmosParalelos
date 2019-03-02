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
    double ancho = 14.0/(5*numHilos);
	printf("ancho por rectangulo: %lf\n", ancho);
	double area_parcial = 0.0;
    double area_total = 0.0;

	//inicia seccion paralela
	#pragma omp parallel private(idHilo,ancho)
	{
        //obtenemos el área a trabajar de cada hilo
		idHilo = omp_get_thread_num();
		printf("Numero de hilo: %i\n", idHilo);
		ancho = 14.0/(5*numHilos);
		double punto_x;;
		double punto_y;
        double i;
        for (i=0;i<5;i++){
			punto_x = (ancho*idHilo*5)+(ancho*i)+3;
            punto_y = 100.0-pow(punto_x-10,4.0)+50.0*pow(punto_x-10,2.0)-8.0*punto_x;
            printf("En el procesador %i, para el punto %lf Y es: %lf\n", idHilo, punto_x, punto_y);
            area_total += punto_y*ancho;
			printf("Se agrega %lf para un area total de %lf\n\n",punto_y*ancho,area_total);
        }
	} //fin de seccion paralela
    printf("Area total: %lf\n", area_total);
	//imprime el resultado
}
