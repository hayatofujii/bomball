/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Tetris: estrutura dos blocos, criação e movimento

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.
*/

typedef struct bloco {
	mem work, temp;

	int tipo, dir;

	void CriaTemp();
//	void SetOnBoard (board *tabuleiro);

	void CriaBloco();
	void Mover (int lin, int col);
//	void Controle (board *tabuleiro);
};

void bloco::CriaTemp () {
	//rotação bloco O
	if (tipo == 0) {
		dir = 0;
        temp.SetMem(0, work.lin[0], work.col[0], corO);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corO);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corO);
			temp.SetMem(3, work.lin[0]+1, work.col[0]-1, corO); 
		}
	//rotação bloco I
	} else if (tipo == 1) {
		dir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corI);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-2, corI);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corI);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corI);
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corI);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corI);
			temp.SetMem(3, work.lin[0]+2, work.col[0]+0, corI);
		}
	//rotação bloco S
	} else if (tipo == 2) {
		dir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corS);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+1, work.col[0]-1, corS);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corS);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corS);
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corS);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corS);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corS);
		}
	//rotação bloco Z
	} else if (tipo == 3) {
		dir %= 2;
		temp.SetMem(0, work.lin[0], work.col[0], corZ);		
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corZ);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corZ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corZ);	
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corZ);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+0, corZ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]-1, corZ);	
		}
	//rotação bloco L
	} else if (tipo == 4) {
		dir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corL);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+1, work.col[0]-1, corL);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corL);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corL);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corL);
		} else if (dir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+1, corL);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corL);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corL);
		} else if (dir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]-1, corL);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+0, corL);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corL);
		}
	//rotação bloco J
	} else if (tipo == 5) {
		dir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corJ);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corJ);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+1, corJ);
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			temp.SetMem(2, work.lin[0]-1, work.col[0]+1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		} else if (dir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]-1, corJ);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corJ);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corJ);
		} else if (dir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corJ);
			temp.SetMem(2, work.lin[0]+1, work.col[0]-1, corJ);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corJ);
		}
	//rotação bloco T
	} else if (tipo == 6) {
		dir %= 4;
		temp.SetMem(0, work.lin[0], work.col[0], corT);
		if (dir == 0) {
			temp.SetMem(1, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(2, work.lin[0]+1, work.col[0]+0, corT);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (dir == 1) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]+1, corT);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		} else if (dir == 2) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(3, work.lin[0]+0, work.col[0]+1, corT);
		} else if (dir == 3) {
			temp.SetMem(1, work.lin[0]-1, work.col[0]+0, corT);
			temp.SetMem(2, work.lin[0]+0, work.col[0]-1, corT);
			temp.SetMem(3, work.lin[0]+1, work.col[0]+0, corT);
		}
	}
}

void bloco::CriaBloco() {
	int lin, col;

	lin = 1;
	col = 6;
	dir = 0;
	
	work.SetMem(0, lin, col, LIGHT_GRAY);
	work.ClearMem(1);
	work.ClearMem(2);
	work.ClearMem(3);

	CriaTemp();
}

/*
void bloco::SetOnBoard (board *tabuleiro) {
	if (!tabuleiro->VerificaEspaco(temp, work)) {
		tabuleiro->DelCellFromMem(work);
		tabuleiro->SetCellFromMem(temp);
		work = temp;
	}
}
*/

//col = -1 vai para a esq.
//col = 1 vai para a dir.
//lin = 1 desce
void bloco::Mover (int lin, int col) {
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
		temp.SetMem(cnt, work.lin[cnt]+lin, work.col[cnt]+col, work.cor[cnt]);
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
