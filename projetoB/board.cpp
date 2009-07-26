/*
http://www.colinfahey.com/tetris/tetris_en.html
*/

#include "work.cpp"


#define corI RED
#define corO BLUE
#define corS CYAN
#define corZ DARK_GRAY
#define corJ YELLOW
#define corL MAGENTA
#define corT GREEN

#define maxLin 18
#define maxCol 10

typedef struct board {
	bool full[maxLin+2][maxCol+2];
	DOS_COLORS cor[maxLin+2][maxCol+2];

	work mem;
	int dir;

	int linhasfull;

	void SetMemCell(int id, int selLin, int selCol, DOS_COLORS selCor);
	void SetCell(int selLin, int selCol, DOS_COLORS selCor);
	void DelCell(int selLin, int selCol);
	void Limpa();
	void CriaBloco(int tipo);
	void Imprime();
	void LinhaCheia();
	bool DetectaOver();


//	bool VerificaAbaixo (int tipo);
//	bool VerificaEspaco (int tipo);
//	void Gira(int tipo, int dir);
//	void Queda();
};

void board::SetMemCell(int id, int selLin, int selCol, DOS_COLORS selCor) {
	full[selLin][selCol] = 1;
	cor[selLin][selCol] = selCor;
	mem.Set(id, selLin, selCol);
}

void board::SetCell(int selLin, int selCol, DOS_COLORS selCor) {
	full[selLin][selCol] = 1;
	cor[selLin][selCol] = selCor;
}

void board::DelCell(int selLin, int selCol) {
	full[selLin][selCol] = false;
}

void board::Limpa() {
	int lin, col;

	linhasfull = 0;
	for (lin = 0; lin < maxLin+2; lin++) {
		for (col = 0; col < maxCol+2; col++) {
            cor[lin][col] = WHITE;
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
				textcolor(cor[lin][col]);
				printf("%c%c", 219, 219);
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

void board::CriaBloco (int tipo) {
	int lin, col;

	//de acordo com a papelada, os blocos vem na 6ª coluna
	lin = 1;
	col = 6;

	//bloco O
	if (tipo == 1) {
		SetMemCell(0, lin, col, corO);
		SetMemCell(1, lin, col-1, corO);
		SetMemCell(2, lin+1, col, corO);
		SetMemCell(3, lin+1, col-1, corO);
	//bloco I
	} else if (tipo == 2) { 
		SetMemCell(0, lin, col, corI);
		SetMemCell(1, lin, col-2, corI);
		SetMemCell(2, lin, col-1, corI);
		SetMemCell(3, lin, col+1, corI);
	//bloco S
	} else if (tipo == 3) {
		SetMemCell(0, lin, col, corS);
		SetMemCell(1, lin+1, col-1, corS);
		SetMemCell(2, lin+1, col, corS);
		SetMemCell(3, lin, col+1, corS);
	//bloco Z
	} else if (tipo == 4) {
		SetMemCell(0, lin, col, corZ);
		SetMemCell(1, lin, col-1, corZ);
		SetMemCell(2, lin+1, col, corZ);
		SetMemCell(3, lin+1, col+1, corZ);	
	//bloco L
	} else if (tipo == 5) {
		SetMemCell(0, lin, col, corL);
		SetMemCell(1, lin+1, col-1, corL);
		SetMemCell(2, lin, col-1, corL);
		SetMemCell(3, lin, col+1, corL);
	//bloco J
	} else if (tipo == 6) {
		SetMemCell(0, lin, col, corJ);
		SetMemCell(1, lin, col-1, corJ);
		SetMemCell(2, lin, col+1, corJ);
		SetMemCell(3, lin+1, col+1, corJ);
	//bloco T
	} else if (tipo == 7) {
		SetMemCell(0, lin, col, corT);
		SetMemCell(1, lin, col-1, corT);
		SetMemCell(2, lin+1, col, corT);
		SetMemCell(3, lin, col+1, corT);
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
