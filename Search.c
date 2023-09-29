#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <threads.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define VECSIZE 10
#define NUM_THREAD 4

struct Result
{
    bool found;
    int idx;
};

struct ThreadData
{
    int idx, length;
};

int vec[VECSIZE];

int target = 3;

struct Result res = {false, -1};

sem_t mutex[VECSIZE];

void* findNum(void* arg)
{
    struct ThreadData* data = (struct ThreadData*) arg;
    
    int curr;

    for (int i = data->idx; i < data->length; i++) {
        curr = vec[i];
        if (curr == target) {
            res.found = true;
            res.idx = i;
            printf("Found number: %d, at index: %d", curr, i);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int length, remainder;
    srand(time(NULL));

    length = VECSIZE / NUM_THREAD; // Tamanho dos dados de cada thread (divisão inteira)
	remainder = VECSIZE % NUM_THREAD; // Resto da divisão inteira

    // Populating the 100 sized array with rand numbers from up to 1000
    for (int i = 0; i < VECSIZE; i++) {
        int num_rand = rand() % 1000 + 1;
        vec[i] = num_rand;
    }
         
    printf("[");
    for (int i = 0; i < VECSIZE; i++) {
        printf("%d", vec[i]);
        if (i != VECSIZE-1) {
            printf(",");
        }
    }
    printf("]");

    pthread_t threads[NUM_THREAD];
    struct ThreadData threadData[NUM_THREAD];

	for(int i = 0; i < NUM_THREAD; i++) {
		threadData[i].idx = i * length;
		threadData[i].length = length;
		if(i == (NUM_THREAD - 1)) { // Testa se é ultima thread
			threadData[i].length += remainder; // A última recebe o resto, além dos dados
        }
        pthread_create(&threads[i], NULL, findNum, &threadData[i]);
	}
}
