// http://www.colinfahey.com/tetris/tetris_en.html

typedef struct bloco {
	mem work;

	int tipo;
	int dir;

	void Gira (int targDir, board *tabuleiro);
	void CriaBloco (board *tabuleiro);
	void Mover (int lin, int col, board *tabuleiro);
//	void Controle (board *tabuleiro);
};

void bloco::Gira (int targDir, board *tabuleiro) {
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
	//rotação bloco I
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
	//rotação bloco S
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
	//rotação bloco Z
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
	//rotação bloco L
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
	//rotação bloco J
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
	//rotação bloco T
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

	if (tabuleiro->VerificaEspaco(temp, work) == false) {
		tabuleiro->DelCellFromMem(work);
		tabuleiro->SetCellFromMem(temp);
		dir = targDir;
		temp.CopyToMem(&work);
	}
}

void bloco::CriaBloco (board *tabuleiro) {
	int lin, col;

	lin = 1;
	col = 6;

	dir = 0;
	
	work.SetMem(0, lin, col, LIGHT_GRAY);
	work.ClearMem(1);
	work.ClearMem(2);
	work.ClearMem(3);

	Gira(dir, tabuleiro);
}

//col = -1 vai para a esq.
//col = 1 vai para a dir.
//lin = 1 desce
void bloco::Mover (int lin, int col, board *tabuleiro) {
	mem temp;
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
		temp.SetMem(cnt, work.lin[cnt]+lin, work.col[cnt]+col, work.cor[cnt]);

	if (tabuleiro->VerificaEspaco(temp, work) == false) {
		tabuleiro->DelCellFromMem(work);
		tabuleiro->SetCellFromMem(temp);
		temp.CopyToMem(&work);
	}
}
/*
void bloco::Controle (board *tabuleiro) {
	char tecla;
	tecla = getch();

	if (tecla == 75)
		Mover(0, -1, tabuleiro);
	else if (tecla == 77)
		Mover(0, 1, tabuleiro);
	else if (tecla == 72)
		Gira(dir+1, tabuleiro);
	else if (tecla == 80)
		Mover(1, 0, tabuleiro);
	else if (tecla == '\r')
		system("pause");
}
*/
