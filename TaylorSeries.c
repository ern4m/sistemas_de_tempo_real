#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define NUMTHREADS  3
#define VETSIZE	    21 // will be the n parameter of the Taylor Series

typedef struct {
	int idx, length;
} thread_arg, *ptr_thread_arg;

pthread_t   threads[NUMTHREADS];  // Threads do programa
thread_arg  arguments[NUMTHREADS];  // Argumentos do programa

sem_t S;

int sum; // Soma geral dos dados
int fact = 1;


float f(float x)
{
    return pow(sin(x), 3) + sqrt(cos(x));
}

long fat(int n)
{
    if(n < 2)
        return 1;
    else
        return n * fat(n-1);    //return (n < 2) ? 1 : n * fat(n-1); 
}

void *taylor_series(void *arg) {
	ptr_thread_arg  argument = (ptr_thread_arg)arg;
	int i, localsum = 0, endidx;
    long fact;
    int x, n;

	endidx = argument->idx + argument->length;  // Posição do ultimo+1
	printf("Somando de %d ate %d\n", argument->idx,endidx);
	for(i = argument->idx; i < endidx; i++) {
        fact = fact*i;
        localsum = localsum + (pow(x,i)/fact) ;
	}
	printf("Soma local %d\n",localsum);
	sem_wait(&S);
	sum += localsum; // Acumula a soma da thread na soma geral (sum = sum+localsum)
	sem_post(&S);
}

int main()
{
    printf("\n\n\t\tStudytonight - Best place to learn\n\n\n");

    int x,i;
    int fact = 1,n;
    float sum=0;
    // n = number of terms in the series
    // x = value of x in the series
    printf("\n\nEnter the value of x in the series :  ");
    scanf("%d",&x);

    printf("\nEnter the number of terms in the series  :   ");
    scanf("%d",&n);

    for(i=1;i<n;i++)
    {
        fact = fact*i;
        sum = sum + (pow(x,i)/fact) ;

    }
    sum = sum + 1; //Since series starts with 1

    printf("\n\nThe sum of the taylor series is :  %.2f\n\n",sum);

    printf("\n\n\n\n\t\t\tCoding is Fun !\n\n\n");
    return 0;
}

int main(int argc, char *argv[])
{
    int i, length, remainder;  // remainder = resto

	sem_init(&S,0,1);
	sum = 0;
    length = VETSIZE / NUMTHREADS; // Tamanho dos dados de cada thread (divisão inteira)
	remainder = VETSIZE % NUMTHREADS; // Resto da divisão inteira
	// Criar todas as threads
	for(i = 0; i < NUMTHREADS; i++) {
		arguments[i].idx = i * length;
		arguments[i].length = length;
		if(i == (NUMTHREADS - 1)) // Testa se é ultima thread
			arguments[i].length += remainder; // A última recebe o resto, além dos dados
		pthread_create(&threads[i], NULL, taylor_series, &arguments[i]);
	}
	// Aguardar todas as threads terminarem
	for(i=0; i<NUMTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	sem_destroy(&S);
	printf("A soma dos numeros de 0 a 4999 eh %d\n", sum);


}
