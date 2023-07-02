#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
pthread_mutex_t mutex;
void *funcion(void *p1);
int c=0;
int suma = 0;

int numeroAlAzar(int limiteSuperior, int limiteInferior)
{
    int valor = rand() % limiteSuperior + limiteInferior;
    return valor;
}

int main()
{
	pthread_t hilo;
	pthread_attr_t attr;
	int error;
    
	pthread_mutex_init(&mutex, NULL);
	pthread_attr_init(&attr);
	error = pthread_create(&hilo, &attr, funcion, NULL);
	 
	if(error != 0)
	{
    	perror("error");
    	return(-1);
	}
    
	int i=0;
    
	 
	while(i<50000)
	{
 	 
   	 c= numeroAlAzar(100, -100);
   	 
   	printf("Numero aleatorio: %d\n", c);
   	suma = suma + c;
 	 
   	pthread_mutex_lock(&mutex);
   	printf("Suma: %d\n", suma);
   	//pthread_mutex_lock(&mutex);
    	i++;
	}
    
   
	pthread_join(hilo,NULL);
    
	pthread_mutex_lock(&mutex);
	return(0);
}

void *funcion(void *p11)
{
	int i=0;	 
	while(i <20)
	{
 
	}
	pthread_exit(0);
}
