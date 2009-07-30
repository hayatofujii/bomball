#include <stdio.h>
#include <stdlib.h>

/*
roadmap
-> criar os blocos
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board está cheia
-> limpar a linha
-> fazer o resto cair
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
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");

		Jogo.Queda();
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");

		Jogo.Gira(rotate);
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
		Jogo.Mover(0, move);
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();

		system("pause");
		system("cls");
		
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
