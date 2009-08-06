// http://www.colinfahey.com/tetris/tetris_en.html

#include "board.cpp"

typedef struct blocos {
	board casas;
	mem work;

	int tipo;
	int dir;

	void CriaBloco();
	void Queda();
	void Gira (int targDir);
	void Mover (int x, int y);
	void Controle();
};

//col = -1 vai para a esq.
//col = 1 vai para a dir.
void blocos::Mover (int lin, int col) {
	mem temp;
	int cnt;
	
	for (cnt = 0; cnt < 4; cnt++)
		temp.SetMem(cnt, work.lin[cnt]+lin, work.col[cnt]+col, work.cor[cnt]);
	
	if (casas.VerificaEspaco(temp, work) == false) {
		casas.DelCellFromMem(work);
		casas.SetCellFromMem(temp);
		temp.CopyToMem(&work);
	}
}

void blocos::Queda() {
	Mover(1, 0);
}

void blocos::Controle() {
	char tecla;
	tecla = getch();

	if (tecla == 75)
		Mover(0, -1);
	else if (tecla == 77)
		Mover(0, 1);
	else if (tecla == 72)
		Gira(dir+1);
	else if (tecla == '\r')
		system("pause");
}

void blocos::Gira (int targDir) {
	mem temp;

	//bloco O
	if (tipo == 0) {
		targDir = 0;
        temp.SetMem(0, work.lin[0], work.col[0], corO);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corO);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corO);
			temp.SetMem(3, work.lin[0]+1, work.col[0]-1, corO); 
		}
	//rota��o bloco I
	} else if (tipo == 1) {
		targDir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corI);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-2, corI);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corI);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corI);
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corI);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corI);
			temp.SetMem(3, work.lin[0]+2, work.col[0]+0, corI);
		}
	//rota��o bloco S
	} else if (tipo == 2) {
		targDir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corS);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+1, work.col[0]-1, corS);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corS);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corS);
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corS);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corS);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corS);
		}
	//rota��o bloco Z
	} else if (tipo == 3) {
		targDir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corZ);		
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corZ);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corZ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corZ);	
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corZ);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+0, corZ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]-1, corZ);	
		}
	//rota��o bloco L
	} else if (tipo == 4) {
		targDir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corL);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+1, work.col[0]-1, corL);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corL);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corL);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corL);
		} else if (targDir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+1, corL);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (targDir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]-1, corL);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+0, corL);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corL);
		}
	//rota��o bloco J
	} else if (tipo == 5) {
		targDir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corJ);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corJ);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corJ);
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		} else if (targDir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]-1, corJ);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corJ);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corJ);
		} else if (targDir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			temp.SetMem(2, work.lin[0]+1, work.col[0]-1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		}
	//rota��o bloco T
	} else if (tipo == 6) {
		targDir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corT);
		if (targDir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corT);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (targDir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corT);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		} else if (targDir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (targDir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		}
	}

	if (casas.VerificaEspaco(temp, work) == false) {
		casas.DelCellFromMem(work);
		casas.SetCellFromMem(temp);
		dir = targDir;
		temp.CopyToMem(&work);
	}
}

void blocos::CriaBloco() {
	int lin, col, dir;

	lin = 1;
	col = 6;
	dir = 0;
	
	work.SetMem(0, lin, col, LIGHT_GRAY);
	work.ClearMem(1);
	work.ClearMem(2);
	work.ClearMem(3);

	Gira(dir);
}