all: SomaThreads  SomaThreadsSemaforo  MatMul

SomaThreads: SomaThreads.c
	gcc -o ./out/SomaThreads SomaThreads.c

SomaThreadsSemaforo: SomaThreadsSemaforo.c
	gcc -o ./out/SomaThreadsSemaforo SomaThreadsSemaforo.c

MatMul: MatMul.c
	gcc -o ./out/MatMul MatMul.c
