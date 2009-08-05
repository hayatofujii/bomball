#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
roadmap
-> criar os blocos -- ok
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board está cheia -- ok
-> limpar a linha -- ok
-> fazer o resto cair  -- ok
*/

#include "blocos.cpp"

int main (void) {
	blocos Jogo;
	
	Jogo.casas.Limpa();

	while (Jogo.casas.DetectaOver() == false) {
		srand(time(NULL));
		Jogo.tipo = rand()%7;
		Jogo.CriaBloco();
		Jogo.casas.Imprime();
		Jogo.work.DebugPrintMemData();
		printf("\n");
		system("pause");
		system("cls");

		while (Jogo.casas.VerificaAbaixo(Jogo.tipo, Jogo.dir, Jogo.work) == false) {
			Jogo.Queda();
			Jogo.casas.Imprime();
			Jogo.work.DebugPrintMemData();
			printf("\n");
			system("pause");
			system("cls");
		}
	}

	printf("\nSaindo!\n");
	system("pause");
}
