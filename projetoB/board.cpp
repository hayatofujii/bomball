#include "defs.c"
#include "mem.cpp"

typedef struct board {
	bool full[maxLin+2][maxCol+2];
	DOS_COLORS cor[maxLin+2][maxCol+2];
	
	int linhasFull;
	
//	void SetCell(int selLin, int selCol, DOS_COLORS selCor);
//	void DelCell(int selLin, int selCol); 

	void SetCellFromMem (mem conf);
	void DelCellFromMem (mem conf);

	void Limpa();
	void Imprime();
	void LinhaCheia();
	bool DetectaOver();
	
	bool VerificaAbaixo (int tipo, int dir, mem reg);
	bool VerificaEspaco (mem reg, mem atual);
};

/*
void board::SetCell (int selLin, int selCol, DOS_COLORS selCor) {
	full[selLin][selCol] = 1;
	cor[selLin][selCol] = selCor;
}

void board::DelCell (int selLin, int selCol) {
	full[selLin][selCol] = 0;
}
*/

void board::SetCellFromMem (mem conf) {
	int cnt;
	for (cnt = 0; cnt < 4; cnt++) {
		full[conf.lin[cnt]][conf.col[cnt]] = 1;
		cor[conf.lin[cnt]][conf.col[cnt]] = conf.cor[cnt];
	}
}

void board::DelCellFromMem (mem conf) {
	int cnt;
	for (cnt = 0; cnt < 4; cnt++)
		if (conf.lin[cnt] != 0 && conf.lin[cnt] != maxLin+1 && conf.col[cnt] != 0 && conf.col[cnt] != maxLin+1)
			full[conf.lin[cnt]][conf.col[cnt]] = 0;
}

//zera o tabuleiro
void board::Limpa() {
	int lin, col;

	linhasFull = 0;
	for (lin = 0; lin < maxLin+2; lin++)
		for (col = 0; col < maxCol+2; col++) {
            cor[lin][col] = LIGHT_GRAY;
			if (lin == 0 || lin == maxLin+1 || col == 0 || col == maxCol+1)
				full[lin][col] = 1;
			else
				full[lin][col] = false;
		}
}

//auto explicativo
void board::Imprime() {
	int lin, col;

	for (lin = 0; lin < maxLin+2; lin++) {
		for (col = 0; col < maxCol+2; col++)
			if (full[lin][col] == 1) {
				textcolor(cor[lin][col]);
				printf("%c%c", 219, 219);
			} else if (full[lin][col] == 0)
				printf("  ");
			else
				printf("%d ", full[lin][col]);
		printf("\n");
	}
	printf("\n\nLinhas completas: %d", linhasFull);
}

//função que zera linhas cheias
void board::LinhaCheia() {
	int lin, col;
	bool verifica[maxLin];

	for (lin = 1; lin < maxLin+1; lin++)
		verifica[lin] = false;

	for (lin = 1; lin < maxLin+1; lin++)
		for (col = 1; col < maxCol+1; col++)
			verifica[lin] |=  full[lin][col];

	for (lin = 1; lin < maxLin+1; lin++)
		if (verifica[lin] == true) {
			for (col = 1; col < maxCol+1; col++)
				full[lin][col] = full[lin-1][col];
			linhasFull++;
		}
}

//detecta game over
bool board::DetectaOver() {
	bool detecta;
	int lin, col;

	detecta = false;
	for (lin = 1; lin < 3; lin++)
		for (col = 3; col < 8; col++)
			detecta |= full[lin][col];

	return detecta;
}

//o VerificaAbaixo é hardcodado pois existem blocos que só checam
//2 ou 3 blocos em baixo
bool board::VerificaAbaixo (int tipo, int dir, mem check) {
	bool verify;
	
	verify = false;
	//bloco O
	if (tipo == 0) {
		if (dir == 0) {
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco I
	} else if (tipo == 1) {
		if (dir == 0) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1) {
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco S
	} else if (tipo == 2) {
		if (dir == 0) {
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco Z
	} else if (tipo == 3) {
		if (dir == 0) {
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco L
	} else if (tipo == 4) {
		if (dir == 0) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1) {
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 2) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 3) {
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco J
	} else if (tipo == 5) {
		if (dir == 0) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1 || dir == 3) {
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 2) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	//bloco T
	} else if (tipo == 6) {
		if (dir == 0) {
			verify |= full[check.lin[1]+1][check.col[1]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 1 || dir == 3) {
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		} else if (dir == 2) {
			verify |= full[check.lin[0]+1][check.col[0]];
			verify |= full[check.lin[2]+1][check.col[2]];
			verify |= full[check.lin[3]+1][check.col[3]];
		}
	}

	return verify;
}

bool board::VerificaEspaco (mem check, mem atual) {
	int cntC, cntA;
	bool ignore[4];
	bool verify;

	verify = false;

	for (cntC = 0; cntC < 4; cntC++)
		ignore[cntC] = false;

	for (cntC = 0; cntC < 4; cntC++)
		for (cntA = 0; cntA < 4; cntA++)
			if (check.lin[cntC] == atual.lin[cntA] && check.col[cntC] == atual.col[cntA])
				ignore[cntC] = true;

	for (cntC = 0; cntC < 4; cntC++)
		if (ignore[cntC] == false)
			verify |= full[check.lin[cntC]][check.col[cntC]];

	return verify;
}
