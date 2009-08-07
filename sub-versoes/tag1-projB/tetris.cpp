#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "defs.c"
#include "funcs.c"
#include "mem.cpp"
#include "board.cpp"
#include "bloco.cpp"

typedef struct jogo {
	board mesa;
	bloco minoes;

	float vel;
	int linhas, nivel;

	void CalculaNivel();
	void CalculaVel();
	void Imprime();
	void Controle();
	void Inicializa();
};

void jogo::CalculaNivel() {
	if (linhas <= 0)
		nivel = 1;
	else if (linhas >= 1 && linhas <= 90)
		nivel = 1 + ((linhas - 1) / 10);
	else if (linhas >= 91)
		nivel = 10;
}

void jogo::CalculaVel() {
     vel = ((11 - nivel)*0.05);
}

void jogo::Imprime() {
	mesa.Imprime();
//	printf("\n\nNivel %d\nLinhas completas: %d\nVelocidade: %.2fs\n", nivel, linhas, vel);
	printf("\n\nNivel %d\nLinhas completas: %d\n", nivel, linhas);
	printf("\nAperte:\nESQ. ou DIR. para alterar direcao\nCIMA para alterar rotacao\nBAIXO para acelerar queda\nENTER para pausar\n\n");
};

void jogo::Controle() {
	char tecla;
	tecla = getch();

	if (tecla == 75)
		minoes.Mover(0, -1, &mesa);
	else if (tecla == 77)
		minoes.Mover(0, 1, &mesa);
	else if (tecla == 72)
		minoes.Gira(minoes.dir+1, &mesa);
	else if (tecla == 80)
		minoes.Mover(1, 0, &mesa);
	else if (tecla == '\r')
		system("pause");
}

void jogo::Inicializa() {
	clock_t reg;

	mesa.Limpa();

	linhas = 0;
	CalculaNivel();
	CalculaVel();


	while (mesa.DetectaOver() == false) {
		srand(time(NULL));
		minoes.tipo = rand()%7;
		minoes.CriaBloco(&mesa);

		system("cls");
		Imprime();

		reg = clock();

		while (mesa.VerificaAbaixo(minoes.work) == false) {
			rewind(stdin);
			if (!kbhit()) {
				if (clock() - reg >= vel * CLOCKS_PER_SEC) {
					minoes.Mover(1, 0, &mesa);
					system("cls");
					Imprime();
					reg = clock();
				}
			} else {
				Controle();
				system("cls");
				Imprime();
			}
		}
		mesa.LinhaCheia(&linhas);
		CalculaNivel();
		CalculaVel();
	}
}

int main (void) {
	jogo tetris;

	tetris.Inicializa();
	printf("\nGame over!\n");
	system("pause");
    return 0;
}
