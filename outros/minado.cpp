#include <stdio.h>
#include <stdlib.h>

#define lim 100

typedef struct casa {
	int numero;
	bool status;
};

typedef struct campominado {
	casa mapa[lim][lim];
	int limLin, limCol;
    int qtdBomb;

	//configura e zera o mapa
	void setupMapa();
	//esse aqui já faz a contagem lateral das bombas
	void insereBomba();
	//"jogada" que abre recursivamente
	void abraCasa(int lin, int col);
	//auto-explicativo	
	void imprimeMapa();
	//a jogada em si
	void jogada();

	//funções de debug
	//o uso da verificaBombaDebug(); está integrado dentro de insereBomba();
	void verificaBombaDebug();
	void imprimeMapaDebug();
	void abraCasaDebug(int lin, int col);
};

void campominado::setupMapa() {
	int lin, col;

	do {
		printf("Entre o numero de linhas do mapa  > ");
		scanf("%d", &limLin);
	} while (limLin <= 1 || limLin > lim);
	
	do {
		printf("Entre o numero de colunas do mapa > ");
		scanf("%d", &limCol);
	} while (limCol <= 1 || limCol > lim);

	for (lin = 0; lin <= limLin+1; lin++) {
		for (col = 0; col <= limCol+1; col++) {
			mapa[lin][col].numero = 0;
			mapa[lin][col].status = false;
		}
	}
}

void campominado::insereBomba() {
	int ctBomb;
	int lin, col;
	int linBomb, colBomb;

	do {
		printf("Entre o numero de bombas no mapa  > ");
		scanf("%d", &qtdBomb);
	} while (qtdBomb > limLin*limCol);

	for (ctBomb = 0; ctBomb < qtdBomb; ctBomb++) {
		do {
			printf("Forneca a linha  da bomba %.2d      > ", ctBomb+1);
			scanf("%d", &lin);
			printf("Forneca a coluna da bomba %.2d      > ", ctBomb+1);
			scanf("%d", &col);
		} while  (lin < 1 || lin > limLin || col < 1 || col > limCol);
		mapa[lin][col].numero = -1;
	}

	for (lin = 1; lin <= limLin; lin++) {
		for (col = 1; col <= limCol; col++) {
            ctBomb = 0;
			if (mapa[lin][col].numero == 0) {
				for (linBomb = lin-1; linBomb <= lin+1; linBomb++) {
					for (colBomb = col-1; colBomb <= col+1; colBomb++) {
						if (mapa[linBomb][colBomb].numero == -1) {
							ctBomb++;
						}
					}
				mapa[lin][col].numero = ctBomb;
				}
			}
		}
	}
}

void campominado::abraCasa(int lin, int col) {
	int ctLin, ctCol;

	if (lin > 0 && lin < limLin+1 && col > 0 && col < limCol+1 && mapa[lin][col].status == false) {
		if (mapa[lin][col].numero > 0) {
			mapa[lin][col].status = true;
		} else if (mapa[lin][col].numero == 0) {
			mapa[lin][col].status = true;
			abraCasa(lin-1, col-1);
			abraCasa(lin-1, col);
			abraCasa(lin-1, col+1);
			abraCasa(lin, col-1);
			abraCasa(lin, col+1);
			abraCasa(lin+1, col-1);
			abraCasa(lin+1, col);
			abraCasa(lin+1, col+1);
		}
	}
}

void campominado::imprimeMapa() {
	int lin, col;

	for (lin = 1; lin <= limLin; lin++) {
		for (col = 1; col <= limCol; col++) {
			if (mapa[lin][col].numero != -1 && mapa[lin][col].status == true) {
				printf("%.2d ", mapa[lin][col].numero);
			} else {
				printf("?? ");
			}
		}
		printf("\n");
	}
}

void campominado::jogada() {
	int selLin, selCol;
	bool vida = true;

	printf("\n\n");
	imprimeMapa();

	while (vida == true) {
		do {
			printf("Escolha a linha > ");
			scanf("%d", &selLin);
		} while (selLin < 1 || selLin > limLin);
		
		do {
			printf("Escolha a coluna > ");
			scanf("%d", &selCol);
		} while (selCol < 1 || selCol > limCol);

		abraCasa(selLin, selCol);
		imprimeMapa();

		if (mapa[selLin][selCol].numero == -1) {
			printf("\nKablooey!\nYou fail!\n");
			vida = false;
		}

		printf("\n\n");

	}
}

//////////////////////// funções de debug ////////////////////////
void campominado::abraCasaDebug(int lin, int col) {
	if (lin > 0 && lin < limLin+1 && col > 0 && col < limCol+1 && mapa[lin][col].status == false) {
		if (mapa[lin][col].numero > 0) {
			printf("ALERTA> Posicao [%.2d x %.2d][%d] contem um numero.\n", lin, col, mapa[lin][col].numero);
			mapa[lin][col].status = true;
			printf("Relatorio> Posicao [%.2d x %.2d][%d] aberta com sucesso.\n", lin, col, mapa[lin][col].numero);
		} else if (mapa[lin][col].numero == 0) {
			printf("Relatorio> Abrindo [%.2d x %.2d][%d].\n", lin, col, mapa[lin][col].numero);
			mapa[lin][col].status = true;
			printf("Relatorio> Posicao [%.2d x %.2d][%d] aberta com sucesso.\n", lin, col, mapa[lin][col].numero);

			printf("Relatorio> Verificando vizinhos de [%.2d x %.2d]...\n", lin, col);
			abraCasaDebug(lin-1, col-1);
			abraCasaDebug(lin-1, col);
			abraCasaDebug(lin-1, col+1);
			abraCasaDebug(lin, col-1);
			abraCasaDebug(lin, col+1);
			abraCasaDebug(lin+1, col-1);
			abraCasaDebug(lin+1, col);
			abraCasaDebug(lin+1, col+1);
			printf("Relatorio> Vizinhos de [%.2d x %.2d] verificados com sucesso.\n", lin, col);
		} else {
			printf("AVISO> Posicao [%.2d x %.2d][%d] nao contem valor 0!\n", lin, col, mapa[lin][col].numero);
		}
	} else {
		printf("AVISO> Posicao [%.2d x %.2d][%d] invalida ou ja esta aberta!\n", lin, col, mapa[lin][col].numero);
	}
}

void campominado::verificaBombaDebug() {
	int lin, col;
	int linBomb, colBomb;
	int ctBomb;

	for (lin = 1; lin <= limLin; lin++) {
		for (col = 1; col <= limCol; col++) {
			printf("Zerando ctBomb...\n");
            ctBomb = 0;
			if (mapa[lin][col].numero == 0) {
				printf("Verificando bombas vizinhas a casa [%d x %d].\n", lin, col);
				for (linBomb = lin-1; linBomb <= lin+1; linBomb++) {
					for (colBomb = col-1; colBomb <= col+1; colBomb++) {
						if (mapa[linBomb][colBomb].numero == -1) {
							printf("Bomba identificada em [%d x %d].\n", linBomb, colBomb);
							ctBomb++;
						}
					}
				printf("Inserindo valor %d a casa [%d x %d]...\n", ctBomb ,lin, col);
				mapa[lin][col].numero = ctBomb;
				}
			}
		}
	}
}

void campominado::imprimeMapaDebug() {
	int lin, col;

	for (lin = 1; lin <= limLin; lin++) {
		for (col = 1; col <= limCol; col++) {
			if (mapa[lin][col].numero == -1) {
				printf("%d ", mapa[lin][col].numero);
			} else {
				printf("%.2d ", mapa[lin][col].numero);
			}
		}
		printf("\n");
	}
}

////////////////////////////////////////////////////////////////

int main (void) {
	campominado jogo1;

	jogo1.setupMapa();
	jogo1.insereBomba();
	jogo1.jogada();

	printf("\n\n");
	system("pause");

	return 0;
}
