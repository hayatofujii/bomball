#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "blocos.cpp"

typedef struct jogo {
	blocos sistema;
	clock_t reg;
	float vel;
	int linhas, nivel;

	void CalculaNivel();
	void CalculaVel();
	void Imprime();
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
	sistema.casas.Imprime();
	printf("\n\nNivel %d\nLinhas completas: %d\nVelocidade: %.2fs\n", nivel, linhas, vel);
	printf("\nAperte:\n <- ou -> para alterar direcao\n^ para alterar rotacao\nENTER para pausar\n\n");
};

void jogo::Inicializa() {
	sistema.casas.Limpa();

	linhas = 0;
	CalculaNivel();
	CalculaVel();

	while (sistema.casas.DetectaOver() == false) {
		srand(time(NULL));
		sistema.tipo = rand()%7;
		sistema.CriaBloco();

		system("cls");
		Imprime();

		reg = clock();

		while (sistema.casas.VerificaAbaixo(sistema.work) == false) {
			rewind(stdin);
			if (!kbhit()) {
				if (clock() - reg >= vel * CLOCKS_PER_SEC) {
					sistema.Mover(1, 0);
					system("cls");
					Imprime();
					reg = clock();
				}
			} else {
				sistema.Controle();
				system("cls");
				Imprime();
			}
		}
		sistema.casas.LinhaCheia(&linhas);
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
