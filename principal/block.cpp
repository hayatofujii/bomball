//"bloco" 1x1
typedef struct minibloco {
	int ascii;
	short int color;
	short int backcolor;

	void set(int codasc, short int codcor, short int codback);
	void imprime();
};

void minibloco::set(int codasc, short int codcor, short int codback) {
	ascii = codasc;
	color = codcor;
	backcolor = codback;
}

void minibloco::imprime() {
	textcolor(backcolor*16 + color);
	printf("%c", ascii);
}

//==============================================

typedef struct block {
	//efeitos
	bool e[20];

	//ascii e cor
	minibloco miniblock[3][5];

	//funções ordem 1 -- desenho básico
	void BLOCK(int ascii, short int color, short int backcolor);
	void EFFECT(int i, bool effect);
	void HLINE(int ascii, short int color, short int backcolor, int line);
	void VLINE(int ascii, short int color, short int backcolor, int line);
	void DOT(int ascii, short int color, short int backcolor,int dot);
	void PRINT(int i, int j);
	void PRINTLINE(int i);

	//funções ordem 2 -- desenho dos blocos
	void ZERO();
	void CIRCLE(short int color, short int backcolor);
	void BOARDS(short int color);
	void FIREUP();
	void FIREDOWN();
	void FIRELEFT();
	void FIRERIGHT();
	void FIREHLINE();
	void FIREVLINE();
	void FIRECENTER();
	void NUMBER(int x, short int color);
	void LETTER(char x, short int color);

	//funções ordem 3 -- desenhos mais avançados
	void BOMBERBALL(short int color);
	void BOMBERBALL2();
	void BOMBERDIE();
	void GATE();
	void BOMB1();
	void BOMB2();
	void MONSTER();
	void FIREIT(short int backcolor);
	void BOMBIT(short int backcolor);
	void WALLIT(short int backcolor);
	void LIFEIT(short int backcolor);
	void INVENCIBLEIT(short int backcolor);
	void SBOMBIT(short int backcolor);
	void SFIREIT(short int backcolor);
};

//seta efeitos
void block::EFFECT(int i, bool effect) {
	e[i] = effect;
}

//coloca um bloco 3x5 de cor, fundo e char único
void block::BLOCK(int ascii, short int color, short int backcolor) {
	int lin, col;

	for (lin = 0; lin < 3; lin++) {
		for (col = 0; col < 5; col++) {
			miniblock[lin][col].set(ascii, color, backcolor);
		}
	}
}

//coloca um miniblock em especifico
//o valor de dot começa em (1,1) -> entre 11
void block::DOT(int ascii, short int color, short int backcolor, int dot) {
	int lin, col;

	lin = (dot/10) - 1;
	col = (dot%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
}

//coloca uma linha horizontal numa das 5 de cada block
void block::HLINE(int ascii, short int color, short int backcolor, int lin) {
	int col;

	lin--;
	for (col = 0; col < 5; col++) {
		miniblock[lin][col].set(ascii, color, backcolor);
	}
}

//coloca uma linha vertical numa das 3 de cada block
void block::VLINE(int ascii, short int color, short int backcolor, int col) {
	int lin;

	col--;
	for (lin = 0; lin < 3; lin++) {
		miniblock[lin][col].set(ascii, color, backcolor);
	}
}

//coloca um "circulo"
void block::CIRCLE(short int color, short int backcolor) {
	BLOCK(NR, color, 0);
	DOT(DR, color, backcolor, 11);
	DOT(DR, color, backcolor, 15);
	DOT(UR, color, backcolor, 31);
	DOT(UR, color, backcolor, 35);
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

	BLOCK(0, 0, 0);
	for (i = 0; i < 20; i++) {
		e[i] = false;
	}
}

//// DEFINIÇÕES DOS ELEMENTOS ////
//bloco inquebrável do mapa
void block::BOARDS(short int color) {
	//e[01] = bloco inquebravel
	e[1] = true;
	BLOCK(R1, color, 0);
}

//desenho do fogo, parte de cima
void block::FIREUP() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 11);
	DOT(DR, 12, 0, 12);
	DOT(DR, 12, 0, 14);
	DOT(NR, 0, 0, 15);
	DOT(UR, 12, 14, 22);
	DOT(UR, 12, 14, 24);
	DOT(NR, 14, 0, 23);
	DOT(NR, 14, 0, 32);
	DOT(NR, 15, 0, 33);
	DOT(NR, 14, 0, 34);
}

//desenho do fogo, parte de baixo
void block::FIREDOWN() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 14, 0, 12);
	DOT(NR, 15, 0, 13);
	DOT(NR, 14, 0, 14);
	DOT(DR, 12, 14, 22);
	DOT(NR, 14, 0, 23);
	DOT(DR, 12, 14, 24);
	DOT(NR, 0, 0, 31);
	DOT(UR, 12, 0, 32);
	DOT(UR, 12, 0, 34);
	DOT(NR, 0, 0, 35);
}

//desenho do fogo, parte da esquerda
void block::FIRELEFT() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 11);
	DOT(DR, 12, 0, 12);
	DOT(UR, 12, 14, 14);
	DOT(UR, 12, 14, 15);
	DOT(NR, 14, 0, 23);
	DOT(NR, 14, 0, 24);
	DOT(NR, 15, 0, 25);
	DOT(NR, 0, 0, 31);
	DOT(UR, 12, 0, 32);
	DOT(DR, 12, 14, 34);
	DOT(DR, 12, 14, 35);
}

//desenho do fogo, parte da direita
void block::FIRERIGHT() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(UR, 12, 14, 11);
	DOT(UR, 12, 14, 12);
	DOT(DR, 12, 0, 14);
	DOT(NR, 0, 0, 15);
	DOT(NR, 15, 0, 21);
	DOT(NR, 14, 0, 22);
	DOT(NR, 14, 0, 23);
	DOT(DR, 12, 14, 31);
	DOT(DR, 12, 14, 32);
	DOT(UR, 12, 0, 34);
	DOT(NR, 0, 0, 35);
}

//desenho do fogo, linha horizontal
void block::FIREHLINE() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 15, 0);
	HLINE(DR, 14, 12, 1);
	HLINE(UR, 14, 12, 3);
}

//desenho do fogo, linha vertical
void block::FIREVLINE() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 12, 0);
	VLINE(NR, 14, 0, 2);
	VLINE(NR, 15, 0, 3);
	VLINE(NR, 14, 0, 4);
}

//desenho de fogo, forma de cruz
void block::FIRECENTER() {
	//e[00] = morte
	//e[07] = fire
	e[0] = true;
	e[7] = true;

	BLOCK(NR, 15, 0);
	DOT(DR, 14, 12, 11);
	DOT(NR, 14, 0, 12);
	DOT(NR, 14, 0, 14);
	DOT(DR, 14, 12, 15);
	DOT(UR, 14, 12, 31);
	DOT(NR, 14, 0, 32);
	DOT(NR, 14, 0, 34);
	DOT(UR, 14, 12, 35);
}

//personagem, carinha da Hudson Soft
void block::BOMBERBALL(short int color) {
	//e[16] = bomberball
	e[16] = true;
	CIRCLE(color, 0);
	DOT(VL, 0, 6, 22);
	DOT(NR, 6, 0, 23);
	DOT(VL, 0, 6, 24);
}

//personagem, carinha feliz
void block::BOMBERBALL2(){
	//e[16] = bomberball
	e[16] = true;
	CIRCLE(14, 0);
	DOT(E1, 1, 14, 22);
	DOT(E1, 1, 14, 24);
	DOT(DT, 12, 14, 33);
}

//personagem, morte
void block::BOMBERDIE() {
	CIRCLE(12, 0);
	DOT('x', 0, 15, 22);
	DOT(NR, 15, 0, 23);
	DOT('x', 0, 15, 24);
}

//portão de teleport
void block::GATE() {
	//e[6] = fim da fase
	e[6] = true;

	CIRCLE(9, 0);
	DOT(LT, 11, 9, 22);
	DOT(NR, 11, 0, 23);
	DOT(RT, 11, 9, 24);
}

//bomba, v1
void block::BOMB1() {
	//e[2] = parede quebravel
	//e[4] = bomba
	e[2] = true;
	e[4] = true;

	CIRCLE(1, 12);
	DOT(201, 8, 1, 13);
	DOT(B2, 8, 1, 14);
	DOT(UR, 8, 1, 23);
}

//bomba, v2
void block::BOMB2() {
	//e[2] = parede quebravel
	//e[4] = bomba
	e[2] = true;
	e[4] = true;

	BLOCK(NR, 12, 0);
	DOT(201,8, 12, 13);
	DOT(B2, 8, 12, 14);
	HLINE(NR, 1, 0, 2);
	HLINE(NR, 1, 0, 3);
	DOT(DR, 1, 12, 21);
	DOT(UR, 8, 1, 23);
	DOT(DR, 1, 12, 25);
	DOT(UR, 1, 12, 31);
	DOT(UR, 1, 12, 35);
}

//monstro1
void block::MONSTER() {
	//e[0] = morte
	//e[5] = bicho
	e[0] = true;
	e[5] = true;

	CIRCLE(12, 0);
	HLINE(UT, 12, 0, 1);
	DOT(E2, 0, 12, 22);
	DOT(E3, 0, 12, 24);
	DOT(UT, 0, 12, 33);
}

//itens -- fire up
void block::FIREIT(short int backcolor) {
	//e[3] = item
	//e[8] = fire item
	e[3] = true;
	e[8] = true;

	BLOCK(NR, 12, 0);
	HLINE(DR, 12, 14, 3);
	DOT(NR, backcolor, 0, 11);
	DOT(DR, 12, backcolor, 12);
	DOT(DR, 12, backcolor, 14);
	DOT(NR, backcolor, 0, 15);
	DOT(UR, 12, 14, 22);
	DOT(UR, 14, 15, 23);
	DOT(UR, 12, 14, 24);
	DOT(UR, 12, backcolor, 31);
	DOT(UR, 12, backcolor, 35);
}

//itens -- bomb up
void block::BOMBIT(short int backcolor) {
	//e[3] = item
	//e[9] = bomb item
	e[3] = true;
	e[9] = true;

	CIRCLE(1, backcolor);
	DOT(201, 8, 1, 13);
	DOT(B2, 8, 1, 14);
	DOT(UR, 8, 1, 23);
}

//itens -- cross wall
void block::WALLIT(short int backcolor) {
	//e[3] = item
	//e[10] = wall item
	e[3] = true;
	e[10] = true;

	BLOCK(SQ, 12, backcolor);
	VLINE('=', 12, backcolor, 1);
	VLINE('=', 12, backcolor, 2);
}

//itens - 1up
void block::LIFEIT(short int backcolor) {
	//e[3] = item
	//e[11] = life item
	e[3] = true;
	e[11] = true;

	CIRCLE(15, backcolor);
	DOT(VL, 0, 6, 22);
	DOT(NR, 6, 0, 23);
	DOT(VL, 0, 6, 24);
}

void block::INVENCIBLEIT(short int backcolor) {
	//e[3] = item
	//e[15] = invencible item
	e[3] = true;
	e[15] = true;

	BLOCK(NR, 6, backcolor);
	HLINE(UT, 6, backcolor, 1);
	DOT(LG, 2, 6, 21);
	DOT(LG, 2, 6, 23);
	DOT(LG, 2, 6, 25);
}

void block::SBOMBIT(short int backcolor) {
	//e[3] = item
	//e[13] = super bomb item
	e[3] = true;
	e[13] = true;

	CIRCLE(1, backcolor);
	DOT(201, 8, 1, 13);
	DOT(B2, 8, 1, 14);
	DOT(LT, 7, 1, 21);
	DOT(UR, 8, 1, 23);
	DOT(RT, 7, 1, 25);
	DOT(DT, 7, 1, 32);
	DOT(DT, 7, 1, 34);
}

void block::SFIREIT(short int backcolor) {
	//e[3] = item
	//e[14] = super fire item
	e[3] = true;
	e[14] = true;

	CIRCLE(12, backcolor);
	DOT(NR, backcolor, 0, 11);
	DOT(DR, 12, backcolor, 12);
	DOT(DR, 12, backcolor, 14);
	DOT(NR, backcolor, 0, 15);
}

//GUI - numeros
void block::NUMBER(int x, short int color) {
	//e[01] = bloco inquebravel
	e[1] = true;

	VLINE(0, 0, 0, 2);
	VLINE(0, 0, 0, 3);
	VLINE(0, 0, 0, 4);
	switch (x) {
		case 0: {
			VLINE(NR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(NR, color, 0, 4);
			DOT(UR, color, 0, 32);
			DOT(UR, color, 0, 34);
			DOT(0, color, 0, 23);
			break;
		}
		case 1: {
			VLINE(NR, color, 0, 3);
			DOT(UR, color, 0, 33);
			DOT(UR, color, 0, 12);
			break;
		}
		case 2: {
			VLINE(UR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(UR, color, 0, 4);
			DOT(NR, color, 0, 14);
			DOT(NR, color, 0, 22);
			break;
		}
		case 3: {
			VLINE(UR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(UR, color, 0, 4);
			DOT(NR, color, 0, 14);
			DOT(NR, color, 0, 24);
			break;
		}
		case 4: {
			VLINE(NR, color, 0, 4);
			DOT(NR, color, 0, 12);
			DOT(UR, color, 0, 22);
			DOT(UR, color, 0, 23);
			DOT(UR, color, 0, 34);
			break;
		}
		case 5: {
			VLINE(UR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(UR, color, 0, 4);
			DOT(NR, color, 0, 12);
			DOT(NR, color, 0, 24);
			break;
		}
		case 6: {
			VLINE(NR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(UR, color, 0, 4);
			DOT(UR, color, 0, 32);
			DOT(NR, color, 0, 24);
			break;
		}
		case 7: {
			VLINE(NR, color, 0, 4);
			DOT(NR, color, 0, 12);
			DOT(UR, color, 0, 13);
			DOT(UR, color, 0, 34);
			break;
		}
		case 8: {
			VLINE(NR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(NR, color, 0, 4);
			DOT(UR, color, 0, 32);
			DOT(UR, color, 0, 34);
			break;
		}
		case 9: {
			VLINE(UR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			VLINE(NR, color, 0, 4);
			DOT(NR, color, 0, 12);
			DOT(UR, color, 0, 34);
			break;
		}
	}
}

//GUI - letras
void block::LETTER(char x, short int color) {
	//e[01] = bloco inquebrável
	e[1] = true;

	ZERO();
	if (x == 'a' || x == 'A') {
		VLINE(NR, color, 0, 1);
		VLINE(NR,color, 0, 4);
		DOT(UR, color, 0, 12);
		DOT(UR, color, 0, 13);
		DOT(UR, color, 0, 22);
		DOT(UR, color, 0, 23);
		DOT(UR, color, 0, 31);
		DOT(UR, color, 0, 34);
	} else if (x == 'b' || x == 'B') {
		VLINE(NR, color, 0, 1);
		VLINE(UR, color, 0, 2);
		VLINE(UR, color, 0, 3);
		VLINE(DR, color, 0, 4);
		DOT(UR, color, 0, 31);
		DOT(0, color, 0, 34);
	} else if (x == 'c' || x == 'C') {
		BLOCK(UR, color, 0);
		HLINE(0, color, 0, 2);
		VLINE(0, color, 0, 5);
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 21);
	} else if (x == 'd' || x == 'D') {
		BLOCK(UR, color, 0);
		DOT(NR, color, 0, 11);
		DOT(DR, color, 0, 14);
		HLINE(NR, color, 0, 2);
		DOT(0, color, 0, 22);
		DOT(0, color, 0, 23);
		DOT(0, color, 0, 34);
		VLINE(0, color, 0, 5);
	} else if (x == 'e' || x == 'E') {
		BLOCK(UR, color, 0);
		VLINE(0, 0, 0, 5);
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 21);
	} else if (x == 'f' || x == 'F') {
		BLOCK(UR, color, 0);
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 21);
		HLINE(0, color, 0, 3);
		DOT(UR, color, 0, 31);
		VLINE(0, color, 0, 5);
	} else if (x == 'g' || x == 'G') {
		BLOCK(UR, color, 0);
		VLINE(0, 0, 0, 5);
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 21);
		DOT(0, color, 0, 22);
		DOT(NR, color, 0, 24);
	} else if (x == 'h' || x == 'H') {
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		DOT(UR, color, 0, 22);
		DOT(UR, color, 0, 23);
		DOT(UR, color, 0, 31);
		DOT(UR, color, 0, 34);
	} else if (x == 'i' || x == 'I') {
		VLINE(NR, color, 0, 2);
		VLINE(NR, color, 0, 3);
		DOT(UR, color, 0, 32);
		DOT(UR, color, 0, 33);
	} else if (x == 'j' || x == 'J') {
		VLINE(NR, color, 0, 4);
		HLINE(UR, color, 0, 3);
		DOT(DR, color, 0, 21);
		DOT(0, color, 0, 35);
	} else if (x == 'k' || x == 'K') {
		VLINE(NR, color, 0, 1);
		VLINE(UR, color, 0, 4);
		DOT(DR, color, 0, 13);
		DOT(UR, color, 0, 22);
		DOT(DR, color, 0, 23);
		DOT(0, color, 0, 24);
		DOT(UR, color, 0, 31);
	} else if (x == 'l' || x == 'L') {
		VLINE(NR, color, 0, 1);
		HLINE(UR, color, 0, 3);
		DOT(0, color, 0, 35);
	} else if (x == 'm' || x == 'M') {
		BLOCK(NR,color, 0);
		DOT(DR, color, 0, 12);
		DOT(DR, color, 0, 13);
		DOT(UT, 0, color, 22);
		DOT(UT, 0, color, 23);
		HLINE(UR, color, 0, 3);
		DOT(0, color, 0, 32);
		DOT(0, color, 0, 33);
		VLINE(0, color, 0, 5);
	} else if (x == 'n' || x == 'N') {
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		DOT(DR, color, 0, 12);
		DOT(UR, color, 0, 23);
		DOT(UR, color, 0, 31);
		DOT(UR, color, 0, 34);
	} else if (x == 'o' || x == 'O') {
		BLOCK(UR, color, 0);
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		DOT(0, color, 0, 22);
		DOT(0, color, 0, 23);
		HLINE(UR, color, 0, 3);
		VLINE(0, color, 0, 5);
	} else if (x == 'p' || x == 'P') {
		BLOCK(UR, color, 0);
		VLINE(NR, color, 0, 1);
		DOT(NR, color, 0, 14);
		HLINE(0, color, 0, 3);
		DOT(UR, color, 0, 31);
		VLINE(0, color, 0, 5);
	} else if (x == 'q' || x == 'Q') {
		BLOCK(UR, color, 0);
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		DOT(0, color, 0, 22);
		DOT(DR, color, 0, 23);
		HLINE(UR, color, 0, 3);
		VLINE(0, color, 0, 5);
	} else if (x == 'r' || x == 'R') {
		BLOCK(UR, color, 0);
		DOT(NR, color, 0, 11);
		DOT(DR, color, 0, 14);
		DOT(NR, color, 0, 21);
		DOT(NR, color, 0, 23);
		DOT(0, color, 0, 24);
		DOT(0, color, 0, 32);
		VLINE(0, color, 0, 5);
	} else if (x == 's' || x == 'S') {
		BLOCK(UR, color, 0);
		VLINE(0, 0, 0, 5);
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 24);
	} else if (x == 't' || x == 'T') {
		HLINE(UR, color, 0, 1);
		VLINE(NR, color, 0, 2);
		VLINE(NR, color, 0, 3);
		DOT(0, color, 0, 15);
		DOT(UR, color, 0, 32);
		DOT(UR, color, 0, 33);
	} else if (x == 'u' || x == 'U') {
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		HLINE(UR, color, 0, 3);
		DOT(0, color, 0, 35);
	} else if (x == 'v' || x == 'V') {
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		HLINE(0, color, 0, 3);
		DOT(UR, color, 0, 32);
		DOT(UR, color, 0, 33);
	} else if (x == 'w' || x == 'W') {
		VLINE(NR, color, 0, 1);
		VLINE(NR, color, 0, 4);
		HLINE(UR, color, 0, 3);
		DOT(DT, 0, color, 22);
		DOT(DT, 0, color, 23);
		DOT(0, color, 0, 35);
	} else if (x == 'x' || x == 'X') {
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 14);
		DOT(DR, color, 0, 21);
		DOT(UR, color, 0, 22);
		DOT(UR, color, 0, 23);
		DOT(DR, color, 0, 24);
		DOT(UR, color, 0, 31);
		DOT(UR, color, 0, 34);
	} else if (x == 'y' || x == 'Y') {
		DOT(NR, color, 0, 11);
		DOT(NR, color, 0, 14);
		DOT(UR, color, 0, 21);
		DOT(NR, color, 0, 22);
		DOT(NR, color, 0, 23);
		DOT(UR, color, 0, 24);
		DOT(UR, color, 0, 32);
		DOT(UR, color, 0, 33);
	} else if (x == 'z' || x == 'Z') {
		BLOCK(UR, color, 0);
		VLINE(0, color, 0, 5);
		DOT(NR, color, 0, 14);
		DOT(0, color, 0, 24);
		DOT(DR, color, 0, 21);
	} else if (x == '!') {
		VLINE(UR, color, 0, 3);
		DOT(NR, color, 0, 13);
	}
}
