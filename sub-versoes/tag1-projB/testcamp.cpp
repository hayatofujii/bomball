#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "funcs.c"
#include "defs.c"
#include "mem.cpp"
#include "board.cpp"
#include "bloco.cpp"

int main (void) {
	board campo;
	bloco minos;
	int bloco, rotate, move;
	
	printf("Entre tipo bloco > ");
	scanf("%d", &bloco);
	printf("Entre tipo rotacao > ");
	scanf("%d", &rotate);	
	printf("Entre movimento lateral > ");
	scanf("%d", &move);

    while (bloco < 7) {
		campo.Limpa();
		system("cls");

		minos.tipo = bloco;
		minos.CriaBloco(&campo);
		printf("Bloco criado com sucesso\n");
		campo.Imprime();
		minos.work.DebugPrintMemData();

		system("pause");
		system("cls");

		if (campo.VerificaAbaixo(minos.work) == false) {
			minos.Mover(1, 0, &campo);
			printf("Queda() efetuado com sucesso\n");
		}
		campo.Imprime();
		minos.work.DebugPrintMemData();
		system("pause");
		system("cls");

		minos.Gira(rotate, &campo);
		printf("Gira(%d) feita com sucesso\n", rotate);
		campo.Imprime();
		minos.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
		minos.Mover(0, move, &campo);
		printf("Mover(0, %d) feito com sucesso\n", move);
		campo.Imprime();
		minos.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
		while (campo.VerificaAbaixo(minos.work) == false) {
			minos.Mover(1, 0, &campo);
			printf("Queda() efetuado com sucesso\n");
			campo.Imprime();
			minos.work.DebugPrintMemData();
			system("pause");
			system("cls");
		}
	
		printf("Entre um numero > ");
		scanf("%d", &bloco);
		printf("Entre outro numero > ");
		scanf("%d", &rotate);
		printf("Entre movimento lateral > ");
		scanf("%d", &move);
	}

	printf("\nSaindo!\n");
	system("pause");
}
