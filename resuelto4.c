#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3

int buffer[BUF_SIZE];
int add=0;
int rem=0;
int num=0;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_cons=PTHREAD_COND_INITIALIZER;
pthread_cond_t c_prod=PTHREAD_COND_INITIALIZER;

void *productor(void *param);
void *consumidor(void *param);

int main (int argc, char *argv[]){
    pthread_t tid1, tid2;
    int i;
    if (pthread_create(&tid1,NULL,productor,NULL) != 0) {
   	 fprintf (stderr, "No se puede crear un hilo de productor\n");
   	 exit (1);
    }
    if (pthread_create(&tid2,NULL,consumidor,NULL) != 0) {
   	 fprintf (stderr, "No se puede crear un hilo de consumidor\n");
   	 exit (1);
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return(0);
}

void *productor(void *param)
{
    int i;
    for (i=1; i<=20; i++) {
   	 pthread_mutex_lock (&m);
   	 if (num > BUF_SIZE) exit(1);
   	 while (num == BUF_SIZE)
   		 pthread_cond_wait (&c_prod, &m);
   	 buffer[add] = i;
   	 add = (add+1) % BUF_SIZE;
   	 num++;
   	 pthread_mutex_unlock (&m);
   	 pthread_cond_signal (&c_cons);
   	 printf ("Productor: insertando %d\n", i);  fflush (stdout);
    }
    printf ("Productor saliendo\n");  fflush (stdout);
}

void *consumidor(void *param)
{
    int i;
    while (1) {
   	 pthread_mutex_lock (&m);
   	 if (num < 0) exit(1);
   	 while (num == 0)
   		 pthread_cond_wait (&c_cons, &m);
   	 i = buffer[rem];
   	 rem = (rem+1) % BUF_SIZE;
   	 num--;
   	 pthread_mutex_unlock (&m);
   	 pthread_cond_signal (&c_prod);
   	 printf ("Valor del consumo %d\n", i);  fflush(stdout);
    }
}
