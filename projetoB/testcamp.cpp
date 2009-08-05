#include <stdio.h>
#include <stdlib.h>

/*
roadmap
-> criar os blocos -- ok
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board est� cheia -- ok
-> limpar a linha -- ok
-> fazer o resto cair  -- ok
*/

#include "blocos.cpp"

int main (void) {
	blocos Jogo;
	int bloco, rotate, move;
	
	printf("Entre tipo bloco > ");
	scanf("%d", &bloco);
	printf("Entre tipo rotacao > ");
	scanf("%d", &rotate);	
	printf("Entre movimento lateral > ");
	scanf("%d", &move);

    while (bloco < 7) {
		Jogo.casas.Limpa();
		system("cls");

		Jogo.tipo = bloco;		
		Jogo.CriaBloco();
		printf("Bloco criado com sucesso\n");
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");

		if (Jogo.casas.VerificaAbaixo(Jogo.tipo, Jogo.dir, Jogo.work) == false) {
			Jogo.Queda();
			printf("Queda() efetuado com sucesso\n");
		}
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();
		system("pause");
		system("cls");

		Jogo.Gira(rotate);
		printf("Gira(%d) feita com sucesso\n", rotate);
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
		Jogo.Mover(0, move);
		printf("Mover(0, %d) feito com sucesso\n", move);
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
		while (Jogo.casas.VerificaAbaixo(Jogo.tipo, Jogo.dir, Jogo.work) == false) {
			Jogo.Queda();
			printf("Queda() efetuado com sucesso\n");
			Jogo.casas.Imprime();
			Jogo.work.DebugPrintMemData();
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