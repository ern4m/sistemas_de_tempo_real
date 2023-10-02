all: SomaThreads  SomaThreadsSemaforo  MatMul Search Pi_approx

SomaThreads: SomaThreads.c
	gcc -o ./out/SomaThreads SomaThreads.c

SomaThreadsSemaforo: SomaThreadsSemaforo.c
	gcc -o ./out/SomaThreadsSemaforo SomaThreadsSemaforo.c

MatMul: MatMul.c
	gcc -o ./out/MatMul MatMul.c

Search: Search.c
	gcc -o ./out/Search Search.c

Pi_approx: Pi_approx.c
	gcc -o ./out/Pi_approx Pi_approx.c -lm
