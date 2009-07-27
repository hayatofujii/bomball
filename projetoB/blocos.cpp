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
	void Gira(int tipo, int dir);
};

void blocos::CriaBloco (int tipo) {
	int lin, col;
	mem setup;

	lin = 1;
	col = 6;

	//bloco O
	if (tipo == 0) {
		setup.SetMem(0, lin+0, col+0, corO);
		setup.SetMem(1, lin+0, col-1, corO);
		setup.SetMem(2, lin+1, col+0, corO);
		setup.SetMem(3, lin+1, col-1, corO);     
	//bloco I
	} else if (tipo == 1) { 
		setup.SetMem(0, lin+0, col+0, corI);
		setup.SetMem(1, lin+0, col-2, corI);
		setup.SetMem(2, lin+0, col-1, corI);
		setup.SetMem(3, lin+0, col+1, corI);
	//bloco S
	} else if (tipo == 2) {
		setup.SetMem(0, lin+0, col+0, corS);
		setup.SetMem(1, lin+1, col-1, corS);
		setup.SetMem(2, lin+1, col+0, corS);
		setup.SetMem(3, lin+0, col+1, corS);
	//bloco Z
	} else if (tipo == 3) {
		setup.SetMem(0, lin+0, col+0, corZ);
		setup.SetMem(1, lin+0, col-1, corZ);
		setup.SetMem(2, lin+1, col+0, corZ);
		setup.SetMem(3, lin+1, col+1, corZ);	
	//bloco L
	} else if (tipo == 4) {
		setup.SetMem(0, lin+0, col+0, corL);
		setup.SetMem(1, lin+1, col-1, corL);
		setup.SetMem(2, lin+0, col-1, corL);
		setup.SetMem(3, lin+0, col+1, corL);
	//bloco J
	} else if (tipo == 5) {
		setup.SetMem(0, lin+0, col+0, corJ);
		setup.SetMem(1, lin+0, col-1, corJ);
		setup.SetMem(2, lin+0, col+1, corJ);
		setup.SetMem(3, lin+1, col+1, corJ);
	//bloco T
	} else if (tipo == 6) {
		setup.SetMem(0, lin+0, col+0, corT);
		setup.SetMem(1, lin+0, col-1, corT);
		setup.SetMem(2, lin+1, col+0, corT);
		setup.SetMem(3, lin+0, col+1, corT);
	}

	casas.SetCellFromMem(setup);
	setup.CopyToMem(&work);
	dir = 0;
}

void blocos::Queda() {
	mem setup;
	int cnt;
	
	casas.DelCellFromMem(work);
	for (cnt = 0; cnt < 4; cnt++) {
		setup.SetMem(cnt, work.lin[cnt]+1, work.col[cnt], work.cor[cnt]);
	}
	casas.SetCellFromMem(setup);
	setup.CopyToMem(&work);
}

void blocos::Gira (int tipo, int targDir) {
	mem rotate;

	casas.DelCellFromMem(work);
	
    //bloco 0, sempre esta em 0,0
	rotate.SetMem(0, work.lin[0], work.col[0], work.cor[0]);

	//bloco O
	if (tipo == 0) {
		if (targDir == 0) {     
			rotate.SetMem(1, work.lin[1], work.col[1], work.cor[1]);
			rotate.SetMem(2, work.lin[2], work.col[2], work.cor[2]);
			rotate.SetMem(3, work.lin[3], work.col[3], work.cor[3]);
		}
	//rotação bloco I
	} else if (tipo == 1) {
		if (targDir == 0) {     
			rotate.SetMem(1, work.lin[0]+0, work.col[0]-2, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+2, work.col[0]+0, work.cor[3]);
		}
	//rotação bloco S
	} else if (tipo == 2) {
		if (targDir == 0) {     
			rotate.SetMem(1, work.lin[0]+1, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]+1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+1, work.cor[3]);
		}
	//rotação bloco Z
	} else if (tipo == 3) {
		if (targDir == 0) {
			rotate.SetMem(1, work.lin[0]+0, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+1, work.cor[3]);	
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]+1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+1, work.cor[3]);	
		}
	//rotação bloco L
	} else if (tipo == 4) {
		if (targDir == 0) {
			rotate.SetMem(1, work.lin[0]+1, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+1, work.cor[3]);
		} else if (targDir == 2) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 3) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]-1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+0, work.cor[3]);
		}
	//rotação bloco J
	} else if (tipo == 5) {
		if (targDir == 0) {
			rotate.SetMem(1, work.lin[0]+0, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]+1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+1, work.cor[3]);
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]-1, work.col[0]+1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+0, work.cor[3]);
		} else if (targDir == 2) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 3) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+0, work.cor[3]);
		}
	//rotação bloco T
	} else if (tipo == 6) {
		if (targDir == 0) {
			rotate.SetMem(1, work.lin[0]+0, work.col[0]-1, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+1, work.col[0]+0, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 1) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]+1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+0, work.cor[3]);
		} else if (targDir == 2) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+0, work.col[0]+1, work.cor[3]);
		} else if (targDir == 3) {
			rotate.SetMem(1, work.lin[0]-1, work.col[0]+0, work.cor[1]);
			rotate.SetMem(2, work.lin[0]+0, work.col[0]-1, work.cor[2]);
			rotate.SetMem(3, work.lin[0]+1, work.col[0]+0, work.cor[3]);
		}
	}

	dir = targDir;      
	casas.SetCellFromMem(rotate);
	rotate.CopyToMem(&work);
}

