all: MatMul Search Pi_approx

MatMul: MatMul.c
	gcc -o ./out/MatMul MatMul.c

Search: Search.c
	gcc -o ./out/Search Search.c

Pi_approx: Pi_approx.c
	gcc -o ./out/Pi_approx Pi_approx.c -lm
