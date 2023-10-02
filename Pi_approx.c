#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <sys/time.h>

#define NUM_TERMS 100
#define NUM_THREADS 4

double pi = 0.0;
sem_t sem;
int terms_per_thread;

// As args to be able to separete what to calculate
// the thread only needs to know which one it is
// beacause with only that it can know what part of the summ it will perform
void* pi_approx(void* arg)
{
    int thread_id = *(int*)arg;
    int start = thread_id * terms_per_thread;
    int end = (thread_id == (NUM_THREADS - 1)) ? NUM_TERMS : start + terms_per_thread;

    double local_sum = 0.0;

    // Calculating terms using sumation
    for (int i = start; i < end; i++) {
        double term = 1.0/(2*i+1);
        if (i % 2 == 0) {
            local_sum += term;
        } else {
            local_sum -= term;
        }
    }
    
    // Using semaphore to access pi variable;
    sem_wait(&sem);
    pi += local_sum;
    sem_post(&sem);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];

    struct timeval start_time, end_time;

    int thread_ids[NUM_THREADS];

    terms_per_thread = NUM_TERMS / NUM_THREADS;

    // initialize semaphore
    sem_init(&sem, 0, 1);

    // initialize time get
    gettimeofday(&start_time, NULL);

    // creating threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, &pi_approx, &thread_ids[i]);
    }

    // finalizing threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // end time
    gettimeofday(&end_time, NULL);


    // time elapsed
    double time_elapsed = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_usec - start_time.tv_usec) / 1e6);

    printf("Estimated Pi value calculated: %lf\n", 4 * pi);
    printf("Time elapsed: %.6f seconds;\n", time_elapsed);

    // destroy sem
    sem_destroy(&sem);
    
    return 0;
}
