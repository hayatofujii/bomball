typedef struct board {
	bool full[maxLin+2][maxCol+2];
	DOS_COLORS cor[maxLin+2][maxCol+2];

//	void SetCell (int selLin, int selCol, DOS_COLORS selCor);
//	void DelCell (int selLin, int selCol);
	void DelLine (int selLin);

	void SetCellFromMem (mem conf);
	void DelCellFromMem (mem conf);

	void Limpa();
	void Imprime();
	void LinhaCheia (int *ctlinha);
	bool DetectaOver();

	bool VerificaEspaco (mem reg, mem atual);
	bool VerificaAbaixo (mem atual);
	
	void CopyFromAbove (int lin);
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

void board::DelLine (int selLin) {
	int col;

	for (col = 1; col < maxCol+1; col++)
		full[selLin][col] = 0;
}

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

//zera tudo
void board::Limpa() {
	int lin, col;

	for (lin = 0; lin < maxLin+2; lin++)
		for (col = 0; col < maxCol+2; col++) {
			cor[lin][col] = LIGHT_GRAY;
			if (lin == 0 || lin == maxLin+1 || col == 0 || col == maxCol+1)
				full[lin][col] = 1;
			else
				full[lin][col] = false;
		}
}

//autoexplicativo
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
}

//detecta game over
bool board::DetectaOver() {
	bool detecta;
	int col;

	detecta = false;
	for (col = 3; col < 8; col++)
		detecta |= full[1][col];

	return detecta;
}

//verifica espaço para girar ou fazer drop
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

//verifica espaço para dropar (é o verifica abaixo adaptado)
bool board::VerificaAbaixo (mem atual) {
	mem temp;
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
		temp.SetMem(cnt, atual.lin[cnt]+1, atual.col[cnt]+0, atual.cor[cnt]);

	return VerificaEspaco(temp, atual);
}

//faz tudo cair
//recursivo!!
void board::CopyFromAbove (int selLin) {
	int lin, col;
	int verifica[maxLin];

	for (lin = 1; lin < maxLin+1; lin++)
		verifica[lin] = 0;

	for (lin = 1; lin < maxLin+1; lin++)
		for (col = 1; col < maxCol+1; col++)
			verifica[lin] += full[lin][col];

	if (verifica[selLin] == 0) {
//		printf("Apagando linha %d.\n", selLin);
		DelLine(selLin);
	} else {
//		printf("Enviando linha %d para a linha %d.\n", selLin-1, selLin);
		for (col = 1; col < maxCol+1; col++) {
			full[selLin][col] = full[selLin-1][col];
			cor[selLin][col] = cor[selLin-1][col];
		}
//		printf("Inicializando sequencia recursiva para a linha %d.\n", selLin-1);
		CopyFromAbove(selLin-1);
//		printf("Fim da sequencia recursiva para a linha %d.\n", selLin-1);
	}
}

//limpa linha cheia e mexe na pontuação
void board::LinhaCheia (int *ctlinha) {
	int lin, col;
	int verifica[maxLin];

	for (lin = 1; lin < maxLin+1; lin++)
		verifica[lin] = 0;

	for (lin = 1; lin < maxLin+1; lin++)
		for (col = 1; col < maxCol+1; col++)
			verifica[lin] += full[lin][col];

	for (lin = 1; lin < maxLin+1; lin++)
		if (verifica[lin] == maxCol) {
//			printf("Ding! Linha %d esta cheia: %d elementos.\n", lin, verifica[lin]);
			CopyFromAbove(lin);
//			*ctlinha = *ctlinha + 1;
			(*ctlinha)++;
//			system("pause");
		}
}
