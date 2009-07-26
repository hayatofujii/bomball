/*
http://www.colinfahey.com/tetris/tetris_en.html
*/

#include "work.cpp"

#define maxLin 18
#define maxCol 10

typedef struct board {
	int full[maxLin+2][maxCol+2];

	work mem;
	int dir;

	int linhasfull;

	void SetCell(int selLin, int selCol, int cor);
	void DelCell(int selLin, int selCol);
	void Limpa();
	void CriaBloco(int id, int tipo, pos posicao);
	void Imprime();
	void LinhaCheia();
	bool DetectaOver();


//	bool VerificaAbaixo (int tipo);
//	bool VerificaEspaco (int tipo);
//	void Gira(int tipo, int dir);
//	void Queda();
};

void board::SetCell(int id, int selLin, int selCol, int cor) {
	full[selLin][selCol] = true;
	cor[selLin][selCol] = cor;
	mem.Set(id, selLin, selCol);
}

void board::DelCell(int selLin, int selCol) {
	full[selLin][selCol] = false;
}

void board::Limpa() {
	int lin, col;

	linhasfull = 0;
	for (lin = 0; lin < maxLin+2; lin++) {
		for (col = 0; col < maxCol+2; col++) {
			if (lin == 0 || lin == maxLin+1 || col == 0 || col == maxCol+1) {
				full[lin][col] = 1;
			} else {
				full[lin][col] = false;
			}
		}
	}
}

void board::Imprime() {
	int lin, col;

	for (lin = 0; lin < maxLin+2; lin++) {
		for (col = 0; col < maxCol+2; col++) {
			if (full[lin][col] == 1) {
				printf("x ");
			} else if (full[lin][col] == 0) {
				printf("  ");
			} else {
				printf("%d ", full[lin][col]);
			}
		}
		printf("\n");
	}
	printf("\n\nLinhas completas: %d", linhasfull);
}

void board::LinhaCheia() {
	int lin, col;
	bool verifica[maxLin];

	for (lin = 1; lin < maxLin+1; lin++) {
		verifica[lin] = false;
	}

	for (lin = 1; lin < maxLin+1; lin++) {
		for (col = 1; col < maxCol+1; col++) {
			verifica[lin] = verifica[lin] || full[lin][col];
		}
	}

	for (lin = 1; lin < maxLin+1; lin++) {
		if (verifica[lin] == true) {
			for (col = 1; col < maxCol+1; col++) {
				full[lin][col] = full[lin-1][col];
			}
			linhasfull++;
		}
	}
}

bool board::DetectaOver() {
	bool detecta;
	int col;

	detecta = true;
	for (col = 3; col < 7; col++) {
		detecta = detecta || full[0][col];
	}
	return detecta;
}

//de acordo com a papelada, os blocos vem na 6� coluna
void board::CriaBloco (int tipo, pos posicao) {
	//bloco central em (0,0)
	SetCell(1, posicao.lin, posicao.col);


	//bloco O
	if (tipo == 1) {
		SetCell(1, posicao.lin, posicao.col-1, corO);
		SetCell(2, posicao.lin-1, posicao.col, corO);
		SetCell(3, posicao.lin-1, posicao.col-1, corO);
			
		mem.Set(1, selLin, selCol);
	//bloco I
	} else if (tipo == 2) { 
		SetCell(1, posicao.lin, posicao.col-2, corI);
		SetCell(2, posicao.lin, posicao.col-1, corI);
		SetCell(3, posicao.lin, posicao.col+1, corI);
	//bloco S
	} else if (tipo == 3) {
		SetCell(1, posicao.lin-1, posicao.col-1, corS);
		SetCell(2, posicao.lin-1, posicao.col, corS);
		SetCell(3, posicao.lin, posicao.col+1, corS);
	//bloco Z
	} else if (tipo == 4) {
		SetCell(1, posicao.lin, posicao.col-1, corZ);
		SetCell(2, posicao.lin-1, posicao.col, corZ);
		SetCell(3, posicao.lin-1, posicao.col+1, corZ);	
	//bloco L
	} else if (tipo == 5) {
		SetCell(1, posicao.lin-1, posicao.col-1, corL);
		SetCell(2, posicao.lin, posicao.col-1, corL);
		SetCell(3, posicao.lin, posicao.col+1, corL);
	//bloco J
	} else if (tipo == 6) {
		SetCell(1, posicao.lin, posicao.col-1, corJ);
		SetCell(2, posicao.lin, posicao.col+1, corJ);
		SetCell(3, posicao.lin-1, posicao.col+1, corJ);
	//bloco T
	} else if (tipo == 7) {
		SetCell(1, posicao.lin, posicao.col-1, corT);
		SetCell(2, posicao.lin-1, posicao.col, corT);
		SetCell(3, posicao.lin, posicao.col+1, corT);
	}
	dir = 0;
}

/*
WORK IN PROGRESS
void board::Gira (int tipo, int targDir) {
	DesetWork(work[0]);
	DesetWork(work[1]);
	DesetWork(work[2]);
	DesetWork(work[3]);

	if (tipo == 0) {
		if (targDir == 1) {
			SetCell(work[0].lin, work[0].col);
			SetCell(work[1].lin, work[1].col-1);
			SetCell(work[2].lin, work[2].col-2);
			SetCell(work[3].lin, work[3].col-3);
			dir = 1;
		} else if (targDir == 0) {
			SetCell(work[0].lin, work[0].col);
			SetCell(work[1].lin+1, min[1].col);
			SetCell(work[2].lin+2, min[2].col);
			SetCell(work[3].lin+3, min[3].col);
			dir = 0;
		}
	} else if (tipo == 1) {
*/
