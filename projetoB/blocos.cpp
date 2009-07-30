// http://www.colinfahey.com/tetris/tetris_en.html

#include "board.cpp"

typedef struct blocos {
	board casas;
	mem work;

	int dir;

	void CriaBloco(int tipo);
	void Queda();
	void Gira (int tipo, int dir);
	void Mover (int x, int y);
};

//x = -1 vai para a esq.
//x = 1 vai para a dir.
void blocos::Mover (int lin, int col) {
	int cnt;
	
	casas.DelCellFromMem(work);
	for (cnt = 0; cnt < 4; cnt++) {
		work.SetMem(cnt, work.lin[cnt]+lin, work.col[cnt]+col, work.cor[cnt]);
	}
	casas.SetCellFromMem(work);
}

void blocos::Queda() {
	Mover(1, 0);
}

void blocos::Gira (int tipo, int targDir) {
	casas.DelCellFromMem(work);
	
	//bloco O
	if (tipo == 0) {
        work.SetMem(0, work.lin[0], work.col[0], corO);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+0, work.col[0]-1, corO);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corO);
			work.SetMem(3, work.lin[0]+1, work.col[0]-1, corO); 
		}
	//rotação bloco I
	} else if (tipo == 1) {
		work.SetMem(0, work.lin[0], work.col[0], corI);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+0, work.col[0]-2, corI);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corI);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corI);
		} else if (targDir == 1) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corI);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corI);
			work.SetMem(3, work.lin[0]+2, work.col[0]+0, corI);
		}
	//rotação bloco S
	} else if (tipo == 2) {
		work.SetMem(0, work.lin[0], work.col[0], corS);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+1, work.col[0]-1, corS);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corS);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corS);
		} else if (targDir == 1) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corS);
			work.SetMem(2, work.lin[0]+0, work.col[0]+1, corS);
			work.SetMem(3, work.lin[0]+1, work.col[0]+1, corS);
		}
	//rotação bloco Z
	} else if (tipo == 3) {			
		if (targDir == 0) {
			work.SetMem(0, work.lin[0], work.col[0], corZ);
			work.SetMem(1, work.lin[0]+0, work.col[0]-1, corZ);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corZ);
			work.SetMem(3, work.lin[0]+1, work.col[0]+1, corZ);	
		} else if (targDir == 1) {
  			work.SetMem(0, work.lin[2], work.col[2], corZ);
			work.SetMem(1, work.lin[2]-1, work.col[2]+1, corZ);
			work.SetMem(2, work.lin[2]+0, work.col[2]+1, corZ);
			work.SetMem(3, work.lin[2]+1, work.col[2]+0, corZ);	
		}
	//rotação bloco L
	} else if (tipo == 4) {
		work.SetMem(0, work.lin[0], work.col[0], corL);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+1, work.col[0]-1, corL);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (targDir == 1) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corL);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corL);
			work.SetMem(3, work.lin[0]+1, work.col[0]+1, corL);
		} else if (targDir == 2) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+1, corL);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (targDir == 3) {
			work.SetMem(1, work.lin[0]-1, work.col[0]-1, corL);
			work.SetMem(2, work.lin[0]-1, work.col[0]+0, corL);
			work.SetMem(3, work.lin[0]+1, work.col[0]+0, corL);
		}
	//rotação bloco J
	} else if (tipo == 5) {
		work.SetMem(0, work.lin[0], work.col[0], corJ);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+0, work.col[0]-1, corJ);
			work.SetMem(2, work.lin[0]+0, work.col[0]+1, corJ);
			work.SetMem(3, work.lin[0]+1, work.col[0]+1, corJ);
		} else if (targDir == 1) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			work.SetMem(2, work.lin[0]-1, work.col[0]+1, corJ);
			work.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		} else if (targDir == 2) {
			work.SetMem(1, work.lin[0]-1, work.col[0]-1, corJ);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corJ);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corJ);
		} else if (targDir == 3) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			work.SetMem(2, work.lin[0]+1, work.col[0]-1, corJ);
			work.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		}
	//rotação bloco T
	} else if (tipo == 6) {
		work.SetMem(0, work.lin[0], work.col[0], corT);
		if (targDir == 0) {
			work.SetMem(1, work.lin[0]+0, work.col[0]-1, corT);
			work.SetMem(2, work.lin[0]+1, work.col[0]+0, corT);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (targDir == 1) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			work.SetMem(2, work.lin[0]+0, work.col[0]+1, corT);
			work.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		} else if (targDir == 2) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			work.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (targDir == 3) {
			work.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			work.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			work.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		}
	}

	dir = targDir;      
	casas.SetCellFromMem(work);
}

void blocos::CriaBloco (int tipo) {
	int lin, col, dir;

	lin = 1;
	col = 6;
	dir = 0;
	
	work.SetMem(0, lin, col, LIGHT_GRAY);
	work.ClearMem(1);
	work.ClearMem(2);
	work.ClearMem(3);

	Gira(tipo, dir);
}
