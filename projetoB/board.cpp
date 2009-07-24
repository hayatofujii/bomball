/*
== TIPOS DE BLOCOS ==
Bloco I -> 0
Bloco J -> 1
Bloco L -> 2
Bloco O -> 3
Bloco S -> 4
Bloco T -> 5
Bloco Z -> 6

== DIRECOES ==
** o cria gera blocos com dir = 0 **

Bloco 0
-> I em pé = 0 = 2
-> I +/- 180 = 1 = 3

Bloco 1
-> J -90 = 0
-> J em pé = 1
-> J + 90 = 2
-> J +/- 180 = 3

Bloco 2
-> L -90 = 0
-> L em pé = 1
-> L + 90 = 2
-> L +/- 180 = 3

Bloco 3
-> O = 0 = 1 = 2 = 3

Bloco 4
-> S normal = 0 = 2
-> S - 90 = 1 = 3

Bloco 5
-> T +/- 180 = 0
-> T - 90 = 1
-> T normal = 2
-> T + 90

Bloco 6
-> Z normal = 0 = 2
-> Z - 90 = 1 = 3

*/

#define maxLin 18
#define maxCol 10

typedef struct board {
	int full[maxLin+2][maxCol+2];
	int cor[maxLin+2][maxCol+2];

	pos working[4];
	int dir;

	int linhasfull;

	void SetPos(int selLin, int selCol, int cor);
	void DelPos(int selLin, int selCol);
	void Limpa();
	void CriaBloco(int tipo, pos posicao);
	void Imprime();
	void LinhaCheia();
	bool DetectaOver();

//	bool VerificaAbaixo (int tipo);
//	bool VerificaEspaco (int tipo);
//	void Gira(int tipo, int dir);
//	void operator -;
};

void board::SetPos (int selLin, int selCol, int cor) {
//	full[selLin][selCol] = true;
//	cor[selLin][selCol] = cor;
}

void board::DelPos (int selLin, int selCol) {
	full[selLin][selCol] = false;
}

void board::Limpa() {
	int lin, col;

	linhasfull = 0;
	for (lin = 0; lin < maxLin+2; lin++) {
		for (col = 0; col < maxCol+2; col++) {
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
				printf("x ");
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

void board::CriaBloco (int tipo, pos posicao) {
	int cnt;

	//bloco I
	if (tipo == '0') {
		for (cnt = 0; cnt < 4; cnt++) {
			SetPos(posicao.lin + cnt, posicao.col);
		}
	//bloco J
	} else if (tipo == 1) {
		SetPos(posicao.lin, posicao.col);
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin, posicao.col+2);
		SetPos(posicao.lin+1, posicao.col+2);
	//bloco L
	} else if (tipo == 2) {
		SetPos(posicao.lin, posicao.col);
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin, posicao.col+2);
		SetPos(posicao.lin+1, posicao.col);
	//bloco O
	} else if (tipo == 3) {
		SetPos(posicao.lin, posicao.col);
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin+1, posicao.col);
		SetPos(posicao.lin+1, posicao.col+1);
	//bloco S
	} else if (tipo == 4) {
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin, posicao.col+2);
		SetPos(posicao.lin+1, posicao.col);
		SetPos(posicao.lin+1, posicao.col+1);
	//bloco T
	} else if (tipo == 5) {
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin+1, posicao.col);
		SetPos(posicao.lin+1, posicao.col+1);
		SetPos(posicao.lin+1, posicao.col+2);
	//bloco Z
	} else if (tipo == 6) {
		SetPos(posicao.lin, posicao.col);
		SetPos(posicao.lin, posicao.col+1);
		SetPos(posicao.lin+1, posicao.col+1);
		SetPos(posicao.lin+1, posicao.col+2);
	}
	dir = 0;
}
/*
WORK IN PROGRESS
void board::Gira (int tipo, int targDir) {
	work[0].DelPos();
	work[1].DelPos();
	work[2].DelPos();
	work[3].DelPos();

	if (tipo == 0) {
		if (targDir == 1) {
			SetPos(work[0].lin, work[0].col);
			SetPos(work[1].lin, work[1].col-1);
			SetPos(work[2].lin, work[2].col-2);
			SetPos(work[3].lin, work[3].col-3);
			dir = 1;
		} else if (targDir == 0) {
			SetPos(work[0].lin, work[0].col);
			SetPos(work[1].lin+1, min[1].col);
			SetPos(work[2].lin+2, min[2].col);
			SetPos(work[3].lin+3, min[3].col);
			dir = 0;
		}
	} else if (tipo == 1) {
*/
