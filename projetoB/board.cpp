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
	bool VerificaEspaco (mem reg);
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

bool board::DetectaOver() {
	bool detecta;
	int col;

	detecta = true;
	for (col = 3; col < 8; col++)
		detecta |= full[0][col];

	return detecta;
}

bool board::VerificaAbaixo (int tipo, int dir, mem reg) {
	bool verify;
	
	verify = false;
	//bloco O
	if (tipo == 0) {
		if (dir == 0) {
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco I
	} else if (tipo == 1) {
		if (dir == 0) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1) {
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco S
	} else if (tipo == 2) {
		if (dir == 0) {
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco Z
	} else if (tipo == 3) {
		if (dir == 0) {
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco L
	} else if (tipo == 4) {
		if (dir == 0) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1) {
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 2) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 3) {
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco J
	} else if (tipo == 5) {
		reg.SetMem(0, reg.lin[0], reg.col[0], corJ);
		if (dir == 0) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1 || dir == 3) {
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 2) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	//bloco T
	} else if (tipo == 6) {
		reg.SetMem(0, reg.lin[0], reg.col[0], corT);
		if (dir == 0) {
			verify |= full[reg.lin[1]+1][reg.col[1]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 1 || dir == 3) {
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		} else if (dir == 2) {
			verify |= full[reg.lin[0]+1][reg.col[0]];
			verify |= full[reg.lin[2]+1][reg.col[2]];
			verify |= full[reg.lin[3]+1][reg.col[3]];
		}
	}

	return verify;
}

bool board::VerificaEspaco (mem reg) {
	int cnt;
	bool verify;
	
	verify = false;
	
	for (cnt = 0; cnt < 4; cnt++)
		if (verify == false)
			verify |= full[reg.lin[cnt]][reg.col[cnt]];

	return verify;
}
