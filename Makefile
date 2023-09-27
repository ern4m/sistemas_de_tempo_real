all: SomaThreads  SomaThreadsSemaforo

SomaThreads: SomaThreads.c
	gcc -o ./out/SomaThreads SomaThreads.c

SomaThreadsSemaforo: SomaThreadsSemaforo.c
	gcc -o ./out/SomaThreadsSemaforo SomaThreadsSemaforo.c
