all: SomaThreads  SomaThreadsSemaforo  MatMul Search

SomaThreads: SomaThreads.c
	gcc -o ./out/SomaThreads SomaThreads.c

SomaThreadsSemaforo: SomaThreadsSemaforo.c
	gcc -o ./out/SomaThreadsSemaforo SomaThreadsSemaforo.c

MatMul: MatMul.c
	gcc -o ./out/MatMul MatMul.c

search: Search.c
	gcc -o ./out/Search Search.c
