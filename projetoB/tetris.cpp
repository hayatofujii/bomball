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

#include "pos.cpp"
#include "blocos.cpp"

typedef struct board {
	bool casa[18][10];
	int linhasfull;

	void limpa();
	void imprime();
	void linhaCheia();
	bool detectaOver();

};

void board::limpa() {
	int lin, col;

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			casa[lin][col] = false;
		}
	}
}

void board::imprime() {
	int lin, col;

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			printf("%d ", casa[lin][col]);
		}
		printf("\n");
	}
}

void board::linhaCheia() {
	bool linha[18];

	for (lin = 0; lin < 18; lin++) {
		linha[lin] = true;
	}

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			linha[lin] = linha[lin] & casa[lin][col];
		}
	}

	for (lin = 0; lin < 18; lin++) {
		if (linha[lin] == true) {
			for (col = 0; col < 10; col++) {
				casa[lin][col] = casa[lin-1][col]
			}
			linhasfull++;
		}
	}
}

bool board::detectaOver() {
	bool detecta;

	detecta = true;
	for (col = 3; col < 7; col++) {
		detecta = deteca & casa[0][col];
	}

	return detecta;
}

int main (void) {
	printf("\n\n");
	system("pause");
}
