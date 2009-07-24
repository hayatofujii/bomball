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

typedef struct board {
	bool full[18][10];
	int cor[18][10];
	pos working[4];

	int linhasfull;

	void SetPos(int selLin, int selCol, int cor);
	void DesetPos(int selLin, int selCol);
	void Limpa();
	void CriaBloco(int tipo, int selLin);
	void Imprime();
	void LinhaCheia();
	bool DetectaOver();

//	bool VerificaAbaixo (int tipo);
//	bool VerificaEspaco (int tipo);
//	void Gira(int tipo, int dir);
//	void operator -;
};

void board::SetPos (int selLin, int selCol, int cor) {
	full[selLin][selCol] = true;
	cor[selLin][selCol] = cor;
}

void board:DesetPos (int selLin, int selCol) {
	full[selLin][selCol] = false;
}

void board::Limpa() {
	int lin, col;

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			casa[lin][col] = false;
		}
	}
}

void board::Imprime() {
	int lin, col;

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			printf("%d ", casa[lin][col]);
		}
		printf("\n");
	}
}

void board::LinhaCheia() {
	int lin, col;
	bool verifica[18];

	for (lin = 0; lin < 18; lin++) {
		verifica[lin] = true;
	}

	for (lin = 0; lin < 18; lin++) {
		for (col = 0; col < 10; col++) {
			verifica[lin] = verifica[lin] & full[lin][col];
		}
	}

	for (lin = 0; lin < 18; lin++) {
		if (verifica[lin] == true) {
			for (col = 0; col < 10; col++) {
				full[lin][col] = full[lin-1][col]
			}
			linhasfull++;
		}
	}
}

bool board::DetectaOver() {
	bool detecta;

	detecta = true;
	for (col = 3; col < 7; col++) {
		detecta = deteca & casa[0][col];
	}
	return detecta;
}

void board::Cria (int tipo, pos posicao) {
	int cnt;

	//bloco I
	if (tipo == '0') {
		for (cnt = 0; cnt < 4; cnt++) {
			min[cnt].SetPos(posicao.lin + cnt, posicao.col);
		}
	//bloco J
	} else if (tipo == 1) {
		min[0].SetPos(posicao.lin, posicao.col);
		min[1].SetPos(posicao.lin, posicao.col+1);
		min[2].SetPos(posicao.lin, posicao.col+2);
		min[3].SetPos(posicao.lin+1, posicao.col+2);
	//bloco L
	} else if (tipo == 2) {
		min[0].SetPos(posicao.lin, posicao.col);
		min[1].SetPos(posicao.lin, posicao.col+1);
		min[2].SetPos(posicao.lin, posicao.col+2);
		min[3].SetPos(posicao.lin+1, posicao.col);
	//bloco O
	} else if (tipo == 3) {
		min[0].SetPos(posicao.lin, posicao.col);
		min[1].SetPos(posicao.lin, posicao.col+1);
		min[2].SetPos(posicao.lin+1, posicao.col);
		min[3].SetPos(posicao.lin+1, posicao.col+1);
	//bloco S
	} else if (tipo == 4) {
		min[0].SetPos(posicao.lin, posicao.col+1);
		min[1].SetPos(posicao.lin, posicao.col+2);
		min[2].SetPos(posicao.lin+1, posicao.col);
		min[3].SetPos(posicao.lin+1, posicao.col+1);
	//bloco T
	} else if (tipo == 5) {
		min[0].SetPos(posicao.lin, posicao.col+1);
		min[1].SetPos(posicao.lin+1, posicao.col);
		min[2].SetPos(posicao.lin+1, posicao.col+1);
		min[3].SetPos(posicao.lin+1, posicao.col+2);
	//bloco Z
	} else if (tipo == 6) {
		min[0].SetPos(posicao.lin, posicao.col);
		min[1].SetPos(posicao.lin, posicao.col+1);
		min[2].SetPos(posicao.lin+1, posicao.col+1);
		min[3].SetPos(posicao.lin+1, posicao.col+2);
	}
	direcao = 0;
}
/*
WORK IN PROGRESS
void board::Gira (int tipo, int targDir) {

	if (tipo == 0) {
		min[1].ApagaPos();
		min[2].ApagaPos();
		min[3].ApagaPos();
		if (targDir == 1) {
			min[1].SetPos(min[1].lin, min[0].col-1);
			min[2].SetPos(min[2].lin, min[0].col-2);
			min[3].SetPos(min[3].lin, min[0].col-3);
		} else if (targDir == 0 {
			min[1].SetPos(min[1]+1.lin, min[0].col);
			min[2].SetPos(min[2]+2.lin, min[0].col);
			min[3].SetPos(min[3]+3.lin, min[0].col);
		}
	} else if (tipo == 1) {
*/
