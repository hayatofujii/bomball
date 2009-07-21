/*
====  ROADMAP block.e/stage.Effects ====
e[00] = morte/invencivel		fire/monster
e[01] = bloco inquebravel		block NR
e[02] = bloco quebravel			block SQ/bomb
e[03] = item					fireit/bombit/wallit
e[04] = bomb					bomb
e[05] = monster					monster
e[06] = portal					gate
e[07] = fire					fireup/down/left/right/center
e[08] = fire up item			fireit
e[09] = bomb up item			bombit
e[10] = wall cross item			wallit
e[11] = life up item			lifeit
e[12] = timebomb item			tbombit
e[13] = superbomb item			sbombit
e[14] = superfire item			sfireit

Expandível a até e[19], por enquanto.
*/

//"bloco" 1x1
typedef struct minibloco {
	int ascii;
	int color;

	void set(int codasc, int codcor);
	void imprime();
};

void minibloco::set(int codasc, int codcor) {
	ascii = codasc;
	color = codcor;
}

void minibloco::imprime() {
	textcolor(color);
	printf("%c", ascii);
}

typedef struct block {
	//efeitos
	bool e[20];

	//ascii e cor
	minibloco miniblock[3][5];

	//funções ordem 1 -- desenho básico
	void BLOCK(int ascii, int color);
	void EFFECT(int i, bool effect);
	void HLINE(int ascii, int color, int line);
	void VLINE(int ascii, int color, int line);
	void DOT(int ascii, int color, int dot);
	void PRINT(int i, int j);
	void PRINTLINE(int i);

	//funções ordem 2 -- desenho dos blocos
	void ZERO();
	void CIRCLE(int color);
	void BOARDS(int color);
	void FIREUP();
	void FIREDOWN();
	void FIRELEFT();
	void FIRERIGHT();
	void FIREHLINE();
	void FIREVLINE();
	void FIRECENTER();
	void NUMBER(int x, int color);
	void LETTER(char x, int color);

	//funções ordem 3 -- desenhos mais avançados
	void BOMBERBALL(int color);
	void BOMBERBALL2();
	void BOMBERDIE();
	void GATE();
	void BOMB1();
	void BOMB2();
	void MONSTER();
	void FIREIT(int color);
	void BOMBIT(int color);
	void WALLIT(int color);
	void LIFEIT(int color);
};

//seta efeitos
void block::EFFECT(int i, bool effect) {
	e[i] = effect;
}

//coloca um bloco 3x5 de cor e char único
void block::BLOCK(int ascii, int color) {
	int lin, col;

	for (lin = 0; lin < 3; lin++) {
		for (col = 0; col < 5; col++) {
			miniblock[lin][col].set(ascii, color);
		}
	}
}

//coloca um miniblock em especifico
//o valor de dot começa em (1,1) -> entre 11
void block::DOT(int ascii, int color, int dot) {
	int lin, col;

	lin = (dot/10) - 1;
	col = (dot%10) - 1;
	miniblock[lin][col].set(ascii, color);
}

//coloca uma linha horizontal numa das 5 de cada block
void block::HLINE(int ascii, int color, int lin) {
	int col;

	lin--;
	for (col = 0; col < 5; col++) {
		miniblock[lin][col].set(ascii, color);
	}
}

//coloca uma linha vertical numa das 3 de cada block
void block::VLINE(int ascii, int color, int col) {
	int lin;

	col--;
	for (lin = 0; lin < 3; lin++) {
		miniblock[lin][col].set(ascii, color);
	}
}

//coloca um "circulo"
void block::CIRCLE(int color) {
	BLOCK(NR, color);
	DOT(DR, color, 11);
	DOT(DR, color, 15);
	DOT(UR, color, 31);
	DOT(UR, color, 35);
}

//imprime bloco 3x5
void block::PRINT(int x, int y) {
	int col;

	gotoxy(y*5+3, x*3+1);
	for (col = 0; col < 5; col++) {
			miniblock[0][col].imprime();
	}
	gotoxy(y*5+3, x*3+2);
	for (col = 0; col < 5; col++) {
			miniblock[1][col].imprime();
	}
	gotoxy(y*5+3, x*3+3);
	for (col = 0; col < 5; col++) {
			miniblock[2][col].imprime();
	}
	gotoxy(y*5+3, x*3+4);
}

//imprime uma única linha do bloco 3x5
//a idéia é como a impressão "progressiva" como nas TVs
void block::PRINTLINE(int lin) {
	int col;

	lin--;
	for (col = 0; col < 5; col++) {
		miniblock[lin][col].imprime();
	}
}
//zera o bloco inteirinho, bem como seus efeitos
void block::ZERO() {
	int i;

	BLOCK(0, 0);
	for (i = 0; i < 20; i++) {
		e[i] = false;
	}
}

//// DEFINIÇÕES DOS ELEMENTOS ////
//bloco inquebrável do mapa
void block::BOARDS(int color) {
	//e[01] = bloco inquebravel
	e[1] = true;
	BLOCK(R1,color);
}

//desenho do fogo, parte de cima
void block::FIREUP() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12);
	DOT(NR, 0, 11);
	DOT(DR, 12, 12);
	DOT(DR, 12, 14);
	DOT(NR, 0, 15);
	DOT(UR, 14*16+12, 22);
	DOT(UR, 14*16+12, 24);
	DOT(NR, 14, 23);
	DOT(NR, 14, 32);
	DOT(NR, 15, 33);
	DOT(NR, 14, 34);
}

//desenho do fogo, parte de baixo
void block::FIREDOWN() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12);
	DOT(NR, 14, 12);
	DOT(NR, 15, 13);
	DOT(NR, 14, 14);
	DOT(DR, 14*16+12, 22);
	DOT(NR, 14, 23);
	DOT(DR, 14*16+12, 24);
	DOT(NR, 0, 31);
	DOT(UR, 12, 32);
	DOT(UR, 12, 34);
	DOT(NR, 0, 35);
}

//desenho do fogo, parte da esquerda
void block::FIRELEFT() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;
	
	BLOCK(NR, 12);
	DOT(NR, 0, 11);
	DOT(DR, 12, 12);
	DOT(UR, 14*16+12, 14);
	DOT(UR, 14*16+12, 15);
	DOT(NR, 14, 23);
	DOT(NR, 14, 24);
	DOT(NR, 15, 25);
	DOT(NR, 0, 31);
	DOT(UR, 12, 32);
	DOT(DR, 14*16+12,34);
	DOT(DR, 14*16+12,35);
}

//desenho do fogo, parte da direita
void block::FIRERIGHT() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;
	
	BLOCK(NR, 12);
	DOT(UR, 14*16+12, 11);
	DOT(UR, 14*16+12, 12);
	DOT(DR, 12, 14);
	DOT(NR, 0, 15);
	DOT(NR, 15, 21);
	DOT(NR, 14, 22);
	DOT(NR, 14, 23);
	DOT(DR, 14*16+12, 31);
	DOT(DR, 14*16+12, 32);
	DOT(UR, 12, 34);
	DOT(NR, 0, 35);
}

//desenho do fogo, linha horizontal
void block::FIREHLINE() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;
	
	BLOCK(NR,15);
	HLINE(DR,12*16+14,1);
	HLINE(UR,12*16+14,3);
}

//desenho do fogo, linha vertical
void block::FIREVLINE() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12);
	VLINE(NR, 14, 2);
	VLINE(NR, 15, 3);
	VLINE(NR, 14, 4);
}

//desenho de fogo, forma de cruz
void block::FIRECENTER() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR,15);
	DOT(DR, 12*16+14, 11);
	DOT(NR, 14, 12);
	DOT(NR, 14, 14);
	DOT(DR, 12*16+14, 15);
	DOT(UR, 12*16+14, 31);
	DOT(NR, 14, 32);
	DOT(NR, 14, 34);
	DOT(UR, 12*16+14, 35);
}

//personagem, carinha feliz
void block::BOMBERBALL(int color) {
	CIRCLE(color);
	DOT(VL, 6*16, 22);
	DOT(NR, 6, 23);
	DOT(VL, 6*16, 24);
}

//personagem, carinha da Hudson Soft
void block::BOMBERBALL2(){
	CIRCLE(14);
	DOT(E1, 14*16+1, 22);
	DOT(E1, 14*16+1, 24);
	DOT(DT, 14*16+12, 33);
}

//personagem, morte
void block::BOMBERDIE() {
	CIRCLE(12);
	DOT('x', 15*16, 22);
	DOT(NR, 15, 23);
	DOT('x', 15*16, 24);
}

//portão de teleport
void block::GATE() {
	//e[9] = fim da fase
	e[9] = true;

	CIRCLE(9);
	DOT(LT, 16*9+11, 22);
	DOT(NR, 11, 23);
	DOT(RT, 16*9+11, 24);
}

//bomba, v1
void block::BOMB1() {
	//e[2] = parede quebravel
	//e[4] = bomba
	e[2] = true;
	e[4] = true;

	CIRCLE(12*16+1);
	DOT(201, 1*16+8, 13);
	DOT(B2, 1*16+8, 14);
	DOT(UR, 1*16+8, 23);
}

//bomba, v2
void block::BOMB2() {
	//e[2] = parede quebravel
	//e[4] = bomba
	e[2] = true;
	e[4] = true;

	BLOCK(NR, 12);
	DOT(201, 12*16+8, 13);
	DOT(B2, 12*16+8, 14);
	HLINE(NR, 1, 2);
	HLINE(NR, 1, 3);
	DOT(DR, 12*16+1, 21);
	DOT(UR, 1*16+8, 23);
	DOT(DR, 12*16+1, 25);
	DOT(UR, 12*16+1, 31);
	DOT(UR, 12*16+1, 35);
}

//monstro1
void block::MONSTER() {
	//e[0] = morte
	//e[5] = bicho
	e[0] = true;
	e[5] = true;

	CIRCLE(12);
	HLINE(UT,12,1);
	DOT(E2,12*16,22);
	DOT(E3,12*16,24);
	DOT(UT,12*16,33);
}

//itens -- fire up
void block::FIREIT(int color) {
	//e[3] = item
	//e[8] = fire item
	e[3] = true;
	e[8] = true;

	BLOCK(NR,12);
	HLINE(DR,14*16+12,3);
	DOT(NR,color,11);
	DOT(DR,color*16+12,12);
	DOT(DR,color*16+12,14);
	DOT(NR,color,15);
	DOT(UR,14*16+12,22);
	DOT(UR,15*16+14,23);
	DOT(UR,14*16+12,24);
	DOT(UR,color*16+12,31);
	DOT(UR,color*16+12,35);
}

//itens -- bomb up
void block::BOMBIT(int color) {
	//e[3] = item
	//e[9] = bomb item
	e[3] = true;
	e[9] = true;

	CIRCLE(color*16+1);
	DOT(201,1*16+8,13);
	DOT(B2,1*16+8,14);
	DOT(UR,1*16+8,23);
}

//itens -- cross wall
void block::WALLIT(int color) {
	//e[3] = item
	//e[10] = wall item
	e[3] = true;
	e[10] = true;
	
	BLOCK(SQ, color*16+12);
	VLINE('=', color*16+12, 1);
	VLINE('=', color*16+12, 2);
}

//itens - 1up
void block::LIFEIT(int color) {
	//e[3] = item
	//e[11] = life item
	e[3] = true;
	e[11] = true;
	
	CIRCLE(color*16+15);
	DOT(VL, 6*16, 22);
	DOT(NR, 6, 23);
	DOT(VL, 6*16, 24);
}

//GUI - numeros
void block::NUMBER(int x,int color) {
	//e[01] = bloco inquebravel
	e[1] = true;

	VLINE(0, 0, 2);
	VLINE(0, 0, 3);
	VLINE(0, 0, 4);
	switch (x) {
		case 0: {
			VLINE(NR,color,2);
			VLINE(UR,color,3);
			VLINE(NR,color,4);
			DOT(UR,color,32);
			DOT(UR,color,34);
			DOT(0,color,23);
			break;
		}
		case 1: {
			VLINE(NR,color,3);
			DOT(UR,color,33);
			DOT(UR,color,12);
			break;
		}
		case 2: {
			VLINE(UR,color,2);
			VLINE(UR,color,3);
			VLINE(UR,color,4);
			DOT(NR,color,14);
			DOT(NR,color,22);
			break;
		}
		case 3: {
			VLINE(UR,color,2);
			VLINE(UR,color,3);
			VLINE(UR,color,4);
			DOT(NR,color,14);
			DOT(NR,color,24);
			break;
		}
		case 4: {
			VLINE(NR,color,4);
			DOT(NR,color,12);
			DOT(UR,color,22);
			DOT(UR,color,23);
			DOT(UR,color,34);
			break;
		}
		case 5: {
			VLINE(UR,color,2);
			VLINE(UR,color,3);
			VLINE(UR,color,4);
			DOT(NR,color,12);
			DOT(NR,color,24);
			break;
		}
		case 6: {
			VLINE(NR,color,2);
			VLINE(UR,color,3);
			VLINE(UR,color,4);
			DOT(UR,color,32);
			DOT(NR,color,24);
			break;
		}
		case 7: {
			VLINE(NR,color,4);
			DOT(NR,color,12);
			DOT(UR,color,13);
			DOT(UR,color,34);
			break;
		}
		case 8: {
			VLINE(NR,color,2);
			VLINE(UR,color,3);
			VLINE(NR,color,4);
			DOT(UR,color,32);
			DOT(UR,color,34);
			break;
		}
		case 9: {
			VLINE(UR,color,2);
			VLINE(UR,color,3);
			VLINE(NR,color,4);
			DOT(NR,color,12);
			DOT(UR,color,34);
			break;
		}
	}
}

//GUI - letras
void block::LETTER(char x, int color) {
	//e[01] = bloco inquebrável
	e[1] = true;

	ZERO();
	if (x == 'a' || x == 'A') {
		VLINE(NR, color, 1);
		VLINE(NR,color, 4);
		DOT(UR, color, 12);
		DOT(UR, color, 13);
		DOT(UR, color, 22);
		DOT(UR, color, 23);
		DOT(UR, color, 31);
		DOT(UR, color, 34);
	} else if (x == 'b' || x == 'B') {
		VLINE(NR, color, 1);
		VLINE(UR, color, 2);
		VLINE(UR, color, 3);
		VLINE(DR, color, 4);
		DOT(UR, color, 31);
		DOT(0, color, 34);
	} else if (x == 'c' || x == 'C') {
		BLOCK(UR, color);
		HLINE(0, color, 2);
		VLINE(0, color,5);
		DOT(NR, color, 11);
		DOT(NR, color, 21);
	} else if (x == 'd' || x == 'D') {
		BLOCK(UR, color);
		DOT(NR, color, 11);
		DOT(DR, color, 14);
		HLINE(NR, color, 2);
		DOT(0, color, 22);
		DOT(0, color, 23);
		DOT(0, color, 34);
		VLINE(0, color, 5);
	} else if (x == 'e' || x == 'E') {
		BLOCK(UR, color);
		VLINE(0, 0, 5);
		DOT(NR, color, 11);
		DOT(NR, color, 21);
	} else if (x == 'f' || x == 'F') {
		BLOCK(UR, color);
		DOT(NR, color, 11);
		DOT(NR, color, 21);
		HLINE(0, color, 3);
		DOT(UR, color, 31);
		VLINE(0, color, 5);
	} else if (x == 'g' || x == 'G') {
		BLOCK(UR, color);
		VLINE(0, 0, 5);
		DOT(NR, color, 11);
		DOT(NR, color, 21);
		DOT(0, color, 22);
		DOT(NR, color, 24);
	} else if (x == 'h' || x == 'H') {
		VLINE(NR, color, 1);
		VLINE(NR, color, 4);
		DOT(UR, color, 22);
		DOT(UR, color, 23);
		DOT(UR, color, 31);
		DOT(UR, color, 34);
	} else if (x == 'i' || x == 'I') {
		VLINE(NR, color, 2);
		VLINE(NR, color, 3);
		DOT(UR, color, 32);
		DOT(UR, color, 33);
	} else if (x == 'j' || x == 'J') {
		VLINE(NR, color, 4);
		HLINE(UR, color, 3);
		DOT(DR, color, 21);
		DOT(0, color, 35);
	} else if (x == 'k' || x == 'K') {
		VLINE(NR, color, 1);
		VLINE(UR, color, 4);
		DOT(DR, color, 13);
		DOT(UR, color, 22);
		DOT(DR, color, 23);
		DOT(0, color, 24);
		DOT(UR, color, 31);
	} else if (x == 'l' || x == 'L') {
		VLINE(NR, color, 1);
		HLINE(UR, color, 3);
		DOT(0, color, 35);
	} else if (x == 'm' || x == 'M') {
		BLOCK(NR,color);
		DOT(DR,color, 12);
		DOT(DR,color, 13);
		DOT(UT,color*16, 22);
		DOT(UT,color*16, 23);
		HLINE(UR,color, 3);
		DOT(0, color, 32);
		DOT(0, color, 33);
		VLINE(0, color, 5);
	} else if (x == 'n' || x == 'N') {
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		DOT(DR,color,12);
		DOT(UR,color,23);
		DOT(UR,color,31);
		DOT(UR,color,34);
	} else if (x == 'o' || x == 'O') {
		BLOCK(UR,color);
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		DOT(0,color,22);
		DOT(0,color,23);
		HLINE(UR,color,3);
		VLINE(0,color,5);
	} else if (x == 'p' || x == 'P') {
		BLOCK(UR,color);
		VLINE(NR,color,1);
		DOT(NR,color,14);
		HLINE(0,color,3);
		DOT(UR,color,31);
		VLINE(0,color,5);
	} else if (x == 'q' || x == 'Q') {
		BLOCK(UR,color);
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		DOT(0,color,22);
		DOT(DR,color,23);
		HLINE(UR,color,3);
		VLINE(0,color,5);
	} else if (x == 'r' || x == 'R') {
		BLOCK(UR,color);
		DOT(NR,color,11);
		DOT(DR,color,14);
		DOT(NR,color,21);
		DOT(NR,color,23);
		DOT(0,color,24);
		DOT(0,color,32);
		VLINE(0,color,5);
	} else if (x == 's' || x == 'S') {
		BLOCK(UR,color);
		VLINE(0,0,5);
		DOT(NR,color,11);
		DOT(NR,color,24);
	} else if (x == 't' || x == 'T') {
		HLINE(UR,color,1);
		VLINE(NR,color,2);
		VLINE(NR,color,3);
		DOT(0,color,15);
		DOT(UR,color,32);
		DOT(UR,color,33);
	} else if (x == 'u' || x == 'U') {
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		HLINE(UR,color,3);
		DOT(0,color,35);
	} else if (x == 'v' || x == 'V') {
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		HLINE(0,color,3);
		DOT(UR,color,32);
		DOT(UR,color,33);
	} else if (x == 'w' || x == 'W') {
		VLINE(NR,color,1);
		VLINE(NR,color,4);
		HLINE(UR,color,3);
		DOT(DT,color*16,22);
		DOT(DT,color*16,23);
		DOT(0,color,35);
	} else if (x == 'x' || x == 'X') {
		DOT(NR,color,11);
		DOT(NR,color,14);
		DOT(DR,color,21);
		DOT(UR,color,22);
		DOT(UR,color,23);
		DOT(DR,color,24);
		DOT(UR,color,31);
		DOT(UR,color,34);
	} else if (x == 'y' || x == 'Y') {
		DOT(NR,color,11);
		DOT(NR,color,14);
		DOT(UR,color,21);
		DOT(NR,color,22);
		DOT(NR,color,23);
		DOT(UR,color,24);
		DOT(UR,color,32);
		DOT(UR,color,33);
	} else if (x == 'z' || x == 'Z') {
		BLOCK(UR,color);
		VLINE(0,color,5);
		DOT(NR,color,14);
		DOT(0,color,24);
		DOT(DR,color,21);
	} else if (x == '!') {
		VLINE(UR,color,3);
		DOT(NR,color,13);
	}
}
