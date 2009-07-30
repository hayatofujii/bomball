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
	int teste, rotate, move;
	
	printf("Entre tipo bloco > ");
	scanf("%d", &bloco);
	printf("Entre tipo rotacao > ");
	scanf("%d", &rotate);	
	printf("Entre mov > ");
	scanf("%d", &move);

    while (teste < 7) {
		Jogo.casas.Limpa(); 
		system("cls");
		
		Jogo.CriaBloco(bloco);
		Jogo.casas.Imprime();

		printf("\n\n");
		Jogo.work.DebugPrintMemData(0);
		Jogo.work.DebugPrintMemData(1);
		Jogo.work.DebugPrintMemData(2);
		Jogo.work.DebugPrintMemData(3);

		printf("\n");
		system("pause");
		system("cls");

		Jogo.Queda();
		Jogo.casas.Imprime();
		
		printf("\n\n");
		Jogo.work.DebugPrintMemData(0);
		Jogo.work.DebugPrintMemData(1);
		Jogo.work.DebugPrintMemData(2);
		Jogo.work.DebugPrintMemData(3);

		printf("\n");
		system("pause");
		system("cls");

		Jogo.Gira(teste, rotate);
		Jogo.casas.Imprime();

		printf("\n\n");
		Jogo.work.DebugPrintMemData(0);
		Jogo.work.DebugPrintMemData(1);
		Jogo.work.DebugPrintMemData(2);
		Jogo.work.DebugPrintMemData(3);

		printf("\n");
		system("pause");
		system("cls");
		
		Jogo.Mover(move);
		Jogo.casas.Imprime();

		printf("\n\n");
		Jogo.work.DebugPrintMemData(0);
		Jogo.work.DebugPrintMemData(1);
		Jogo.work.DebugPrintMemData(2);
		Jogo.work.DebugPrintMemData(3);
		
		printf("\n");
		system("pause");
		system("cls");
		
		printf("Entre um numero > ");
		scanf("%d", &teste);
		printf("Entre outro numero > ");
		scanf("%d", &rotate);
		printf("Entre mov > ");
		scanf("%d", &move);		
	}

	printf("\nSaindo!\n");
	system("pause");
}
