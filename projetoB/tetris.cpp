#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// quase l�, t� quase pronto!
// s� precisa arrumar sistema de pontua��o, n�vel e velocidade de queda!!
// obviamente tem que arrumar os bugs...

#include "blocos.cpp"

void wait(int milliseconds) {
	clock_t end;
	//soma o n�mero de clock inicial com o n�mero de clocks durante "milliseconds"
	end = clock() + milliseconds * CLOCKS_PER_SEC /1000;
	while (clock() < end);
}

int main (void) {
	blocos Jogo;
	clock_t reg;

	Jogo.casas.Limpa();

	while (Jogo.casas.DetectaOver() == false) {
		srand(time(NULL));
		Jogo.tipo = rand()%7;
		system("cls");
		Jogo.casas.LinhaCheia();
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
	}

	printf("\nSaindo!\n");
	system("pause");
}

