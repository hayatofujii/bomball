/*
http://www.colinfahey.com/tetris/tetris_en.html
*/

#include "board.cpp"

typedef struct blocos {
	board casas;
	work memory;
	int dir;

	int linhasfull;

	void CriaBloco(int tipo);

//	void Gira(int tipo, int dir);
//	void Queda();
};

void blocos::CriaBloco (int tipo) {
	int lin, col;

	//de acordo com a papelada, os blocos vem na 6ª coluna
	lin = 1;
	col = 6;

	//bloco O
	if (tipo == 1) {
		casas.SetMemCell(0, lin, col, corO, memory);
		casas.SetMemCell(1, lin, col-1, corO, memory);
		casas.SetMemCell(2, lin+1, col, corO, memory);
		casas.SetMemCell(3, lin+1, col-1, corO, memory);
	//bloco I
	} else if (tipo == 2) { 
		casas.SetMemCell(0, lin, col, corI, memory);
		casas.SetMemCell(1, lin, col-2, corI, memory);
		casas.SetMemCell(2, lin, col-1, corI, memory);
		casas.SetMemCell(3, lin, col+1, corI, memory);
	//bloco S
	} else if (tipo == 3) {
		casas.SetMemCell(0, lin, col, corS, memory);
		casas.SetMemCell(1, lin+1, col-1, corS, memory);
		casas.SetMemCell(2, lin+1, col, corS, memory);
		casas.SetMemCell(3, lin, col+1, corS, memory);
	//bloco Z
	} else if (tipo == 4) {
		casas.SetMemCell(0, lin, col, corZ, memory);
		casas.SetMemCell(1, lin, col-1, corZ, memory);
		casas.SetMemCell(2, lin+1, col, corZ, memory);
		casas.SetMemCell(3, lin+1, col+1, corZ, memory);	
	//bloco L
	} else if (tipo == 5) {
		casas.SetMemCell(0, lin, col, corL, memory);
		casas.SetMemCell(1, lin+1, col-1, corL, memory);
		casas.SetMemCell(2, lin, col-1, corL, memory);
		casas.SetMemCell(3, lin, col+1, corL, memory);
	//bloco J
	} else if (tipo == 6) {
		casas.SetMemCell(0, lin, col, corJ, memory);
		casas.SetMemCell(1, lin, col-1, corJ, memory);
		casas.SetMemCell(2, lin, col+1, corJ, memory);
		casas.SetMemCell(3, lin+1, col+1, corJ, memory);
	//bloco T
	} else if (tipo == 7) {
		casas.SetMemCell(0, lin, col, corT, memory);
		casas.SetMemCell(1, lin, col-1, corT, memory);
		casas.SetMemCell(2, lin+1, col, corT, memory);
		casas.SetMemCell(3, lin, col+1, corT, memory);
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
