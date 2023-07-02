#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3
#define M 4
#define P 2
#define NUM_THREADS 12

int A[N][M] = {{1, 2, 3, 4},
               {5, 6, 7, 8},
               {9, 10, 11, 12}};

int B[M][P] = {{1, 2},
               {3, 4},
               {5, 6},
               {7, 8}};

int C[N][P];

pthread_mutex_t mutex;

void *multiply(void *arg) {
    int thread_id = *(int *)arg;
    int i, j, k;
    
    for (i = thread_id; i < N; i += NUM_THREADS) {
        for (j = 0; j < P; j++) {
            int sum = 0;
            for (k = 0; k < M; k++) {
                sum += A[i][k] * B[k][j];
            }
            pthread_mutex_lock(&mutex);
            C[i][j] = sum;
            pthread_mutex_unlock(&mutex);
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    
    pthread_mutex_init(&mutex, NULL);
    
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, (void *)&thread_ids[i]);
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    // Imprimir la matriz resultante C
    printf("Matriz resultante C:\n");
    for (i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
