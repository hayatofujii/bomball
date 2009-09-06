/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Tetris: executável principal

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.
*/


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
	void Imprime (bool debug);
	void Controle();
	void Inicializa (bool debug);
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

void jogo::Imprime (bool debug) {
	mesa.Imprime();

	printf("\n\nNivel %d\nLinhas completas: %d\n", nivel, linhas);
	printf("\nAperte:\nESQ. ou DIR. para alterar direcao\nCIMA para alterar rotacao\nBAIXO para acelerar queda\nENTER para pausar\n\n");

	if (debug) {
		printf("Taxa de Atualizacao: %.2fs", vel);
		printf("\nTemporario:");
		minoes.temp.DebugPrintMemData();
		printf("\nAtual:");
		minoes.work.DebugPrintMemData();
		printf("\nDirecao: %d\n\n", minoes.dir);
	}
}

void jogo::Controle() {
	char tecla;
	tecla = getch();

	if (tecla == 75) {
		minoes.Mover(0, -1);
		mesa.SetNewMem(minoes.temp, &minoes.work);
	} else if (tecla == 77) {
		minoes.Mover(0, 1);
		mesa.SetNewMem(minoes.temp, &minoes.work);
	} else if (tecla == 72) {
		minoes.dir++;
		minoes.CriaTemp();
		mesa.SetNewMem(minoes.temp, &minoes.work);
	} else if (tecla == 80) {
		minoes.Mover(1, 0);
		mesa.SetNewMem(minoes.temp, &minoes.work);
	} else if (tecla == '\r')
		system("pause");
}

void jogo::Inicializa (bool debug) {
	clock_t reg;

	mesa.Limpa();
	linhas = 0;
	
	srand(time(NULL));
	minoes.tipo = rand()%7;
	minoes.CriaBloco();
	
	while (!mesa.DetectaOver(minoes.temp)) {
		CalculaNivel();
		CalculaVel();

		mesa.SetNewMem(minoes.temp, &minoes.work);
		
		system("cls");
		Imprime(debug);

		reg = clock();

		while (!mesa.VerificaAbaixo(minoes.work)) {
			rewind(stdin);
			if (!kbhit()) {
				if (clock() - reg >= vel * CLOCKS_PER_SEC) {
					minoes.Mover(1, 0);
					mesa.SetNewMem(minoes.temp, &minoes.work);
					system("cls");
					Imprime(debug);
					reg = clock();
				}
			} else {
				Controle();
				system("cls");
				Imprime(debug);
			}
		}

		mesa.LinhaCheia(&linhas);

		minoes.tipo = rand()%7;
		minoes.CriaBloco();
	} 
}

int main (void) {
	jogo tetris;
	bool continuar;
	
	continuar = true;
	
	while (continuar) {
		tetris.Inicializa(0);
		printf("\nXii... nao vai dar para criar outro bloco.\nEntao e game over!\n");
		printf("\nJogar de novo?\n1. Sim\n2. Nao\n");
		do {
			if (getch() == '1')
				continuar = true;
			else
				continuar = false;
		} while (continuar != true && continuar != false);
	}
	printf("\nSaindo!\n");
	system("pause");
    return 0;
}
