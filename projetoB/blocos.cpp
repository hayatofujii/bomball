/*
http://www.colinfahey.com/tetris/tetris_en.html
*/

#include "board.cpp"

typedef struct blocos {
	board casas;
	mem work;

	int dir;

	void CriaBloco(int tipo);
	void Queda();
//	void Gira(int tipo, int dir);

};

void blocos::CriaBloco (int tipo) {
	int lin, col;

	lin = 1;
	col = 6;

	//bloco O
	if (tipo == 1) {
		casas.SetMemCell(0, lin, col, corO, &work);
		casas.SetMemCell(1, lin, col-1, corO, &work);
		casas.SetMemCell(2, lin+1, col, corO, &work);
		casas.SetMemCell(3, lin+1, col-1, corO, &work);
	//bloco I
	} else if (tipo == 2) { 
		casas.SetMemCell(0, lin, col, corI, &work);
		casas.SetMemCell(1, lin, col-2, corI, &work);
		casas.SetMemCell(2, lin, col-1, corI, &work);
		casas.SetMemCell(3, lin, col+1, corI, &work);
	//bloco S
	} else if (tipo == 3) {
		casas.SetMemCell(0, lin, col, corS, &work);
		casas.SetMemCell(1, lin+1, col-1, corS, &work);
		casas.SetMemCell(2, lin+1, col, corS, &work);
		casas.SetMemCell(3, lin, col+1, corS, &work);
	//bloco Z
	} else if (tipo == 4) {
		casas.SetMemCell(0, lin, col, corZ, &work);
		casas.SetMemCell(1, lin, col-1, corZ, &work);
		casas.SetMemCell(2, lin+1, col, corZ, &work);
		casas.SetMemCell(3, lin+1, col+1, corZ, &work);	
	//bloco L
	} else if (tipo == 5) {
		casas.SetMemCell(0, lin, col, corL, &work);
		casas.SetMemCell(1, lin+1, col-1, corL, &work);
		casas.SetMemCell(2, lin, col-1, corL, &work);
		casas.SetMemCell(3, lin, col+1, corL, &work);
	//bloco J
	} else if (tipo == 6) {
		casas.SetMemCell(0, lin, col, corJ, &work);
		casas.SetMemCell(1, lin, col-1, corJ, &work);
		casas.SetMemCell(2, lin, col+1, corJ, &work);
		casas.SetMemCell(3, lin+1, col+1, corJ, &work);
	//bloco T
	} else if (tipo == 7) {
		casas.SetMemCell(0, lin, col, corT, &work);
		casas.SetMemCell(1, lin, col-1, corT, &work);
		casas.SetMemCell(2, lin+1, col, corT, &work);
		casas.SetMemCell(3, lin, col+1, corT, &work);
	}
	dir = 0;
}

void blocos::Queda() {
	int cnt;
	casas.DelCellMem(work);
	for (cnt = 0; cnt < 4; cnt++) {
		casas.SetMemCell(cnt, work.lin[cnt]+1, work.col[cnt], work.cor[cnt], &work);
	}
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

