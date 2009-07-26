#include "defs.c"
#include "work.cpp"
#include "funcs.c"

typedef struct board {
	bool full[maxLin+2][maxCol+2];
	DOS_COLORS cor[maxLin+2][maxCol+2];
	
	int linhasfull;

	void SetMemCell(int id, int selLin, int selCol, DOS_COLORS selCor, work mem);
	void SetCell(int selLin, int selCol, DOS_COLORS selCor);
	void DelCell(int selLin, int selCol);
	
	void LinhaCheia() ;
	void Imprime();
	void Limpa();
	bool DetectaOver();
	
//	bool VerificaAbaixo (int tipo);
//	bool VerificaEspaco (int tipo);
};

void board::SetMemCell(int id, int selLin, int selCol, DOS_COLORS selCor, work mem) {
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
