#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#define MAT4_SIZE 4

// Define um struct para uma mat4
struct mat4
{
    int data[MAT4_SIZE][MAT4_SIZE];
};

struct ThreadData
{
    int row;
    int col;
};

// Inicialização do array de semaforos 
sem_t mutex[MAT4_SIZE][MAT4_SIZE];

// Criando as matrizes
struct mat4 matA;
struct mat4 matB;
struct mat4 matRES;


void* matMul(void* arg)
{
    struct ThreadData* data = (struct ThreadData*) arg;
    int row = data->row;
    int col = data->col;

    int tmp = 0;
    for (int k = 0; k < MAT4_SIZE; k++) {
        tmp += matA.data[row][k] * matB.data[k][col];
    }
    
    sem_wait(&mutex[row][col]);
    matRES.data[row][col] = tmp;
    sem_post(&mutex[row][col]);

    pthread_exit(NULL);
}

int main()
{
    // Inicializando matA e matB
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            // Atribuição de valores
            matA.data[i][j] = i * MAT4_SIZE + j + 1;
            matB.data[i][j] = i * MAT4_SIZE + j + 1;
        }
    }

    // Criando estrutura de threads
    pthread_t threads[MAT4_SIZE][MAT4_SIZE];
    struct ThreadData threadData[MAT4_SIZE][MAT4_SIZE];

    // time variables
    struct timeval start_time, end_time;

    // Inicializando os semaforos
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            // Estado inicial de todos como disponível
            sem_init(&mutex[i][j], 0, 1);
        }
    }

    // start time
    gettimeofday(&start_time, NULL);

    // Criar as threads
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            // Criando os argumentos para a ThreadData
            // Será a posição de cada row x col que serao multiplicadas
            threadData[i][j].row = i;
            threadData[i][j].col = j;

            // Criando a thread
            pthread_create(&threads[i][j], NULL, matMul, &threadData[i][j]);
        }
    }

    // Esperar o fim das threads
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            // liberando as threads
            pthread_join(threads[i][j], NULL);
        }
    }

    // end time
    gettimeofday(&end_time, NULL);

    // Printar as matrizes
    printf("4x4 Matrix:\n");
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            printf("%d\t", matRES.data[i][j]);
        }
        printf("\n");
    }

    // Destruir os semaforos
    for (int i = 0; i < MAT4_SIZE; i++) {
        for (int j = 0; j < MAT4_SIZE; j++) {
            sem_destroy(&mutex[i][j]);
        }
    }

    double time_elapsed = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_usec - start_time.tv_usec) / 1e6);

    printf("Time elapsed: %.6f seconds;\n", time_elapsed);

    return 0;
}
