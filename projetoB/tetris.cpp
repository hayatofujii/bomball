#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// quase lá, tá quase pronto!
// só precisa arrumar sistema de pontuação, nível e velocidade de queda!!
// obviamente tem que arrumar os bugs...

#include "blocos.cpp"

int main (void) {
	blocos Jogo;
	clock_t reg;

	Jogo.casas.Limpa();

	while (Jogo.casas.DetectaOver() == false) {
		srand(time(NULL));
		Jogo.tipo = rand()%7;
		system("cls");
		Jogo.CriaBloco();
		Jogo.casas.Imprime();
		reg = clock();

		while (Jogo.casas.VerificaAbaixo(Jogo.tipo, Jogo.dir, Jogo.work) == false) {
			rewind(stdin);
			if (!kbhit()) {
				if (clock() - reg >= 0.3 * CLOCKS_PER_SEC) {
					Jogo.Queda();
					system("cls");
					Jogo.casas.Imprime();
					reg = clock();
				}
			} else {
				Jogo.Controle();
				system("cls");
				Jogo.casas.Imprime();
			}
		}

		Jogo.casas.LinhaCheia();
	}

	printf("\nGame over!\n");
	system("pause");
	return 0;
}

