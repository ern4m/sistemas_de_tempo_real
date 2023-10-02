#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define ARRAY_SIZE 100
#define NUM_THREADS 4

int target = 42; // Number to be searched
int found = 0;   // Tmp to check if value was found
int array[ARRAY_SIZE];
sem_t found_sem;
sem_t print_sem;

// Function that each thread will execute to search for the target number
void* search(void* arg) {
    int thread_id = *(int*)arg;
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    // verify if it's the last thread, if true the end of the search will be ARRAY SIZE
    // else it will be the start + values per thread
    int end = (thread_id == (NUM_THREADS - 1)) ? ARRAY_SIZE : start + chunk_size;

    for (int i = start; i < end; i++) {
        if (array[i] == target) {
            sem_wait(&found_sem); // Wait for permission to update found
            if (!found) {
                found = 1; // Set found flag if not already set
            }
            sem_post(&found_sem); // Release the semaphore
            break;
        }
    }

    sem_post(&print_sem); // Signal that this thread has finished searching
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize the array with random values
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100;
    }

    // print array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int a = array[i];
        printf("%d - ", a);
    }
    sem_init(&found_sem, 0, 1); // Initialize the found semaphore
    sem_init(&print_sem, 0, 0); // Initialize the print semaphore

    // Create and launch threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, search, &thread_ids[i]);
    }

    // Wait for all threads to finish searching
    for (int i = 0; i < NUM_THREADS; i++) {
        sem_wait(&print_sem); // Wait for permission to print
    }

    // Check if the number was found
    if (found) {
        printf("Number %d was found.\n", target);
    } else {
        printf("Number %d was not found.\n", target);
    }

    // Clean up semaphores
    sem_destroy(&found_sem);
    sem_destroy(&print_sem);

    return 0;
}
