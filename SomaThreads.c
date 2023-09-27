#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS  2
#define VETSIZE	    26

typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t   threads[NUMTHREADS];  // Threads do programa
thread_arg  arguments[NUMTHREADS];  // Argumentos das threads

unsigned long int sum; // Soma geral dos dados


void *thread_func(void *arg) {
	ptr_thread_arg  argument = (ptr_thread_arg)arg;
	unsigned long int i, localsum = 0, endidx;

	endidx = argument->idx + argument->length;  // Posição do ultimo+1
	printf("Somando de %d ate %lu\n", argument->idx, endidx);
	for(i = argument->idx; i < endidx; i++) {
		localsum += i;  // localsum = localsum+i  (variavel = variavel op valor)
	}                   //                         variavel op = valor
	printf("Soma local %lu\n",localsum);
	sum += localsum; // Acumula a soma da thread na soma geral (sum = sum+localsum)
}


int main(int argc, char **argv) {
	unsigned long int i, length, remainder;  // remainder = resto

	sum = 0;
    length = VETSIZE / NUMTHREADS; // Tamanho dos dados de cada thread (divisão inteira)
	remainder = VETSIZE % NUMTHREADS; // Resto da divisão inteira
	// Criar todas as threads
	for(i = 0; i < NUMTHREADS; i++) {
		arguments[i].idx = i * length;
		arguments[i].length = length;
		if(i == (NUMTHREADS - 1)) // Testa se é ultima thread
			arguments[i].length += remainder; // A última recebe o resto, além dos dados
		pthread_create(&threads[i], NULL, thread_func, &arguments[i]);
	}
	// Aguardar todas as threads terminarem
	for(i=0; i<NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("A soma dos numeros de 0 a %d eh %lu\n", (VETSIZE-1), sum);

}


