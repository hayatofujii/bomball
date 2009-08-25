//"bloco" 1x1
typedef struct minibloco {
	char ascii;
	short int color;
	short int backcolor;

	//funções
	void set(char codasc, short int codcor, short int codback);
	void imprime();
};

void minibloco::set(char codasc, short int codcor, short int codback) {
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
	bool e[10];
	//tipo de item/monstro
	char item, monster;
	//slot da bomba e do monstro
	short int bslot, mslot;

	//ascii e cor
	minibloco miniblock[3][5];

	//***Funções***

	//desenho básico
	void BLOCK(char ascii, short int color, short int backcolor);
	void DOT(char ascii, short int color, short int backcolor, short int dot);
	void DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2);
	void DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2, short int dot3);
	void DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2, short int dot3, short int dot4);
	void HLINE(char ascii, short int color, short int backcolor, short int line);
	void VLINE(char ascii, short int color, short int backcolor, short int line);
	void PRINT(short int i, short int j);
	void PRINTLINE(short int i);

	//desenho dos blocos
	void BOARDS(short int color);
	void CIRCLE(short int color, short int backcolor);
	void SQBLOCK(short int color);
	void ZERO();

	//fogo
	void FIRECENTER();
	void FIREDOWN();
	void FIREHLINE();
	void FIRELEFT();
	void FIRERIGHT();
	void FIREUP();
	void FIREVLINE();

	//GUI
	void LETTER(char x, short int color);
    void NUMBER(short int x, short int color);

	//bombas
	void BOMB1(short int backcolor);
	void BOMB2(short int backcolor);
	void NBOMB1();
	void NBOMB2();
	void SBOMB1();
	void SBOMB2();
	void TBOMB1();
	void TBOMB2();
	void STBOMB1();
	void STBOMB2();

	//monstros/heroi
	void BODY(short int color, char LastMove);
	void BOMBERBALL(short int color, short int backcolor, char LastMove);
	void BOMBERDIE();
	void BOSS(short int color);
	void HERO(short int color, char LastMove);
	void MONSTER(char i);
	void MONSTER1();
	void MONSTER2();
	void MONSTER3();
	void MONSTER4();

	//itens/portal
	void BOMBIT();
	void FIREIT();
	void GATE();
	void INVENCIBLEIT();
	void KICKIT();
	void LIFEIT();
	void PUNCHIT();
	void SBOMBIT();
	void SFIREIT();
	void TBOMBIT();
	void WALLIT();
};

//***desenho básico***

//coloca um bloco 3x5 de cor, fundo e char único
void block::BLOCK(char ascii, short int color, short int backcolor) {
	for (int lin = 0; lin < 3; lin++) {
		for (int col = 0; col < 5; col++) {
			miniblock[lin][col].set(ascii, color, backcolor);
		}
	}
}

//coloca um miniblock em específico
//o valor de dot começa em (1,1) -> entre 11
void block::DOT(char ascii, short int color, short int backcolor, short int dot) {
	int lin, col;

	lin = (dot/10) - 1;
	col = (dot%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
}

void block::DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2) {
    int lin, col;

	lin = (dot1/10) - 1;
	col = (dot1%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot2/10) - 1;
	col = (dot2%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
}

void block::DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2, short int dot3) {
    int lin, col;

	lin = (dot1/10) - 1;
	col = (dot1%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot2/10) - 1;
	col = (dot2%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot3/10) - 1;
	col = (dot3%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
}

void block::DOT(char ascii, short int color, short int backcolor, short int dot1, short int dot2, short int dot3, short int dot4) {
    int lin, col;

	lin = (dot1/10) - 1;
	col = (dot1%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot2/10) - 1;
	col = (dot2%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot3/10) - 1;
	col = (dot3%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
	lin = (dot4/10) - 1;
	col = (dot4%10) - 1;
	miniblock[lin][col].set(ascii, color, backcolor);
}

//coloca uma linha horizontal numa das 5 de cada block
void block::HLINE(char ascii, short int color, short int backcolor, short int lin) {
	lin--;
	for (int col = 0; col < 5; col++) {
		miniblock[lin][col].set(ascii, color, backcolor);
	}
}

//coloca uma linha vertical numa das 3 de cada block
void block::VLINE(char ascii, short int color, short int backcolor, short int col) {
	col--;
	for (int lin = 0; lin < 3; lin++) {
		miniblock[lin][col].set(ascii, color, backcolor);
	}
}

//imprime bloco 3x5
void block::PRINT(short int x, short int y) {
	gotoxy(y*5+3, x*3+1);
	for (int col = 0; col < 5; col++) {
			miniblock[0][col].imprime();
	}
	gotoxy(y*5+3, x*3+2);
	for (int col = 0; col < 5; col++) {
			miniblock[1][col].imprime();
	}
	gotoxy(y*5+3, x*3+3);
	for (int col = 0; col < 5; col++) {
			miniblock[2][col].imprime();
	}
	gotoxy(y*5+3, x*3+4);
}

//imprime uma única linha do bloco 3x5
//a idéia é como a impressão "progressiva" como nas TVs
void block::PRINTLINE(short int lin) {
	lin--;
	for (int col = 0; col < 5; col++) {
		miniblock[lin][col].imprime();
	}
}

//***desenho dos blocos***

//bloco inquebrável do mapa
void block::BOARDS(short int color) {
	//e[01] = bloco inquebravel
	//e[00] = bloco não vazio
	e[0] = e[1] = true;
	BLOCK(R1, color, 0);
}

//coloca um "círculo"
void block::CIRCLE(short int color, short int backcolor) {
	BLOCK(NR, color, 0);
	DOT(DR, color, backcolor, 11, 15);
	DOT(UR, color, backcolor, 31, 35);
}
void block::SQBLOCK(short int color) {
    //e[02] = bloco quebravel
	//e[00] = bloco não vazio
	e[0] = e[2] = true;
	BLOCK(SQ, color, 0);
}

//zera o bloco inteirinho, bem como seus efeitos
void block::ZERO() {
	BLOCK(0, 0, 0);
	for (int i = 0; i < 10; i++) {
		e[i] = false;
	}
	//nenhum item/monstro
	item = monster = '\0';
	//nenhum slot
	bslot = mslot = -1;
}

//***fogo***
    //e[07] = fire
	//e[00] = bloco não vazio

//desenho de fogo, forma de cruz
void block::FIRECENTER() {
	e[0] = e[7] = true;

	BLOCK(NR, 15, 0);
	DOT(DR, 14, 12, 11, 15);
	DOT(NR, 14, 0, 12, 14, 32, 34);
	DOT(UR, 14, 12, 31, 35);
}

//desenho do fogo, parte de baixo
void block::FIREDOWN() {
	e[0] = e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 31, 35);
	DOT(UR, 12, 0, 32, 34);
	DOT(DR, 12, 14, 22, 24);
	DOT(NR, 14, 0, 12, 14, 23);
	DOT(NR, 15, 0, 13);
}

//desenho do fogo, linha horizontal
void block::FIREHLINE() {
	e[0] = e[7] = true;

	BLOCK(NR, 15, 0);
	HLINE(DR, 14, 12, 1);
	HLINE(UR, 14, 12, 3);
}

//desenho do fogo, parte da esquerda
void block::FIRELEFT() {
	e[0] = e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 11, 31);
	DOT(DR, 12, 0, 12);
	DOT(UR, 12, 14, 14, 15);
	DOT(NR, 14, 0, 23, 24);
	DOT(NR, 15, 0, 25);
	DOT(UR, 12, 0, 32);
	DOT(DR, 12, 14, 34, 35);
}

//desenho do fogo, parte da direita
void block::FIRERIGHT() {
	e[0] = e[7] = true;

	BLOCK(NR, 12, 0);
    DOT(UR, 12, 14, 11, 12);
    DOT(DR, 12, 0, 14);
	DOT(NR, 0, 0, 15, 35);
	DOT(NR, 15, 0, 21);
	DOT(NR, 14, 0, 22, 23);
	DOT(DR, 12, 14, 31, 32);
	DOT(UR, 12, 0, 34);
}

//desenho do fogo, parte de cima
void block::FIREUP() {
	e[0] = e[7] = true;

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 11, 15);
	DOT(DR, 12, 0, 12, 14);
	DOT(UR, 12, 14, 22, 24);
	DOT(NR, 14, 0, 23, 32, 34);
	DOT(NR, 15, 0, 33);
}

//desenho do fogo, linha vertical
void block::FIREVLINE() {
	e[0] = e[7] = true;

	BLOCK(NR, 12, 0);
	VLINE(NR, 14, 0, 2);
	VLINE(NR, 15, 0, 3);
	VLINE(NR, 14, 0, 4);
}

//***GUI***

//letras
void block::LETTER(char x, short int color) {
	ZERO();
	if (x == 'a' || x == 'A') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 12, 13, 22, 23);
		DOT(UR, color, 0, 31, 34);
    } else if (x == 'b' || x == 'B') {
		DOT(NR, color, 0, 11, 21);
		DOT(DR, color, 0, 14, 24);
		DOT(UR, color, 0, 31);
		VLINE(UR, color, 0, 2);
		VLINE(UR, color, 0, 3);
    } else if (x == 'c' || x == 'C') {
		DOT(NR, color, 0, 11, 21);
		DOT(UR, color, 0, 12, 13, 14);
		DOT(UR, color, 0, 31, 32, 33, 34);
    } else if (x == 'd' || x == 'D') {
		DOT(NR, color, 0, 11, 21, 24);
		DOT(UR, color, 0, 12, 13);
		DOT(UR, color, 0, 31, 32, 33);
		DOT(DR, color, 0, 14);
    } else if (x == 'e' || x == 'E') {
		BLOCK(UR, color, 0);
		DOT(NR, color, 0, 11, 21);
		VLINE(0, 0, 0, 5);
    } else if (x == 'f' || x == 'F') {
		DOT(NR, color, 0, 11, 21);
		DOT(UR, color, 0, 12, 13, 14);
		DOT(UR, color, 0, 22, 23, 24, 31);
	} else if (x == 'g' || x == 'G') {
		BLOCK(UR, color, 0);
		VLINE(0, 0, 0, 5);
		DOT(NR, color, 0, 11, 21, 24);
		DOT(0, color, 0, 22);
    } else if (x == 'h' || x == 'H') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 22, 23, 31, 34);
    } else if (x == 'i' || x == 'I') {
		DOT(NR, color, 0, 12, 13, 22, 23);
		DOT(UR, color, 0, 32, 33);
    } else if (x == 'j' || x == 'J') {
		DOT(NR, color, 0, 14, 24);
		DOT(UR, color, 0, 31, 32, 33, 34);
		DOT(DR, color, 0, 21);
    } else if (x == 'k' || x == 'K') {
		DOT(NR, color, 0, 11, 21);
		DOT(UR, color, 0, 14, 22, 31, 34);
		DOT(DR, color, 0, 13, 23);
    } else if (x == 'l' || x == 'L') {
		DOT(NR, color, 0, 11, 21);
		DOT(UR, color, 0, 31, 32, 33, 34);
    } else if (x == 'm' || x == 'M') {
		DOT(DR,color, 0, 12, 13);
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 31, 34);
		DOT(UT, 0, color, 22, 23);
    } else if (x == 'n' || x == 'N') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(DR, color, 0, 12);
		DOT(UR, color, 0, 23, 31, 34);
    } else if (x == 'o' || x == 'O') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 12, 13);
		DOT(UR, color, 0, 31, 32, 33, 34);
    } else if (x == 'p' || x == 'P') {
		DOT(NR, color, 0, 11, 14, 21);
		DOT(UR, color, 0, 12, 13, 22, 23);
		DOT(UR, color, 0, 24, 31);
    } else if (x == 'q' || x == 'Q') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 12, 13, 23);
		DOT(UR, color, 0, 31, 32, 33, 34);
		DOT(DR, color, 0, 22);
	} else if (x == 'r' || x == 'R') {
		DOT(NR, color, 0, 11, 21, 23);
		DOT(UR, color, 0, 12, 13, 22);
		DOT(UR, color, 0, 31, 33, 34);
		DOT(DR, color, 0, 14);
    } else if (x == 's' || x == 'S') {
		BLOCK(UR, color, 0);
		VLINE(0, 0, 0, 5);
		DOT(NR, color, 0, 11, 24);
    } else if (x == 't' || x == 'T') {
		DOT(NR, color, 0, 12, 13, 22, 23);
		DOT(UR, color, 0, 11, 14, 32, 33);
	} else if (x == 'u' || x == 'U') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 31, 32, 33, 34);
    } else if (x == 'v' || x == 'V') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 32, 33);
	} else if (x == 'w' || x == 'W') {
		DOT(NR, color, 0, 11, 14, 21, 24);
		DOT(UR, color, 0, 31, 32, 33, 34);
		DOT(DT, 0, color, 22, 23);
    } else if (x == 'x' || x == 'X') {
		DOT(NR, color, 0, 11, 14);
		DOT(DR, color, 0, 21, 24);
		DOT(UR, color, 0, 22, 23, 31, 34);
    } else if (x == 'y' || x == 'Y') {
		DOT(NR, color, 0, 11, 14, 22, 23);
		DOT(UR, color, 0, 21, 24, 32, 33);
    } else if (x == 'z' || x == 'Z') {
		BLOCK(UR, color, 0);
		VLINE(0, color, 0, 5);
		DOT(NR, color, 0, 14);
		DOT(0, color, 0, 24);
		DOT(DR, color, 0, 21);
	} else if (x == '!') {
		DOT(UR, color, 0, 23, 33);
		DOT(NR, color, 0, 13);
	} else if (x == '?') {
	    DOT(DR, color, 0, 11, 14, 23, 33);
	    DOT(UR, color, 0, 12, 13, 24);
    } else if (x == '-') {
        DOT(UR, color, 0, 22, 23, 24);
    } else if (x == '|') {
        DOT(DR, color, 0, 13);
        DOT(NR, color, 0, 23);
    }
}

//números
void block::NUMBER(short int x, short int color) {
	VLINE(0, 0, 0, 2);
	VLINE(0, 0, 0, 3);
	VLINE(0, 0, 0, 4);
	switch (x) {
		case 0: {
			DOT(NR, color, 0, 12, 14, 22, 24);
			DOT(UR, color, 0, 13, 32, 33, 34);
			break;
		}
		case 1: {
			DOT(NR, color, 0, 13, 23);
			DOT(UR, color, 0, 12, 33);
			break;
		}
		case 2: {
			DOT(NR, color, 0, 14, 22);
			VLINE(UR, color, 0, 3);
			DOT(UR, color, 0, 12, 24, 32, 34);
			break;
		}
		case 3: {
			DOT(NR, color, 0, 14, 24);
			DOT(UR, color, 0, 34);
			VLINE(UR, color, 0, 2);
			VLINE(UR, color, 0, 3);
			break;
		}
		case 4: {
			DOT(NR, color, 0, 12, 14, 24);
			DOT(UR, color, 0, 22, 23, 34);
			break;
		}
		case 5: {
			DOT(NR, color, 0, 12, 24);
			DOT(UR, color, 0, 14, 22, 32, 34);
			VLINE(UR, color, 0, 3);
			break;
		}
		case 6: {
			DOT(NR, color, 0, 12, 22, 24);
			DOT(UR, color, 0, 14, 32, 34);
			VLINE(UR, color, 0, 3);
			break;
		}
		case 7: {
			DOT(NR, color, 0, 12, 14, 24);
			DOT(UR, color, 0, 13, 34);
			break;
		}
		case 8: {
			DOT(NR, color, 0, 12, 14, 22, 24);
			DOT(UR, color, 0, 32, 34);
			VLINE(UR, color, 0, 3);
			break;
		}
		case 9: {
			DOT(NR, color, 0, 12, 14, 24);
			DOT(UR, color, 0, 22, 32, 34);
			VLINE(UR, color, 0, 3);
			break;
		}
	}
}

//***bomba***
    //e[4] = bomba
	//e[00] = bloco não vazio

//bomba, v1
void block::BOMB1(short int backcolor) {
	CIRCLE(1, backcolor);
	DOT(201, 8, 1, 13);
	DOT(B2, 8, 1, 14);
	DOT(UR, 8, 1, 23);
}

//bomba, v2
void block::BOMB2(short int backcolor) {
	BLOCK(NR, backcolor, 0);
	DOT(201, 8, backcolor, 13);
	DOT(B2, 8, backcolor, 14);
	DOT(NR, 1, 0, 22, 24);
	DOT(NR, 1, 0, 32, 33, 34);
	DOT(DR, 1, backcolor, 21, 25);
	DOT(UR, 8, 1, 23);
	DOT(UR, 1, backcolor, 31, 35);
}

//bomba normal
void block::NBOMB1() {
	e[0] = e[4] = true;

	BOMB1(12);
}

void block::NBOMB2() {
	e[0] = e[4] = true;

	BOMB2(12);
}

//bomba espinho
void block::SBOMB1() {
	e[0] = e[4] = true;

	BOMB1(12);
	DOT(LT, 7, 1, 21);
	DOT(RT, 7, 1, 25);
	DOT(DT, 7, 1, 32, 34);
}

void block::SBOMB2() {
	e[0] = e[4] = true;

	BOMB2(12);
	DOT(LT, 7, 1, 22);
	DOT(RT, 7, 1, 24);
	DOT(DT, 7, 1, 33);

}

//bomba relógio
void block::TBOMB1() {
    e[0] = e[4] = true;

    BOMB1(12);
    DOT(205, 8, 1, 12, 14);
    DOT(203, 8, 1, 13);
}

void block::TBOMB2() {
    e[0] = e[4] = true;

	BOMB2(12);
    DOT(205, 8, 12, 12, 14);
    DOT(203, 8, 12, 13);
}

//bomba espinho/relogio
void block::STBOMB1() {
    e[0] = e[4] = true;

	BOMB2(12);
    DOT(205, 8, 1, 12, 14);
    DOT(203, 8, 1, 13);
    DOT(LT, 7, 1, 21);
	DOT(RT, 7, 1, 25);
	DOT(DT, 7, 1, 32, 34);
}

void block::STBOMB2() {
    e[0] = e[4] = true;

	BOMB2(12);
    DOT(205, 8, 12, 12, 14);
    DOT(203, 8, 12, 13);
    DOT(LT, 7, 1, 22);
	DOT(RT, 7, 1, 24);
	DOT(DT, 7, 1, 33);
}

//***monstros/heróis***

void block::BODY(short int color, char LastMove) {
    short int color2;
    ZERO();
    //e[8] = bomberball
	//e[00] = bloco não vazio
	e[0] = e[8] = true;

	color2 = 6;
	if (color == 15) {
	    color = 1;
	    color2 = 15;
	}

	DOT(NR, color, 0, 12, 13, 14);
	DOT(UR, 0, color, 22, 23, 24);
	DOT(DR, color2, 0, 11, 15);
	DOT(DR, 13, color2, 21, 25);
	if (LastMove == KEY_UP || LastMove == KEY_DOWN) {
	    DOT(DR, 13, color2, 32, 34);
    } else {
	    DOT(NR, color2, 0, 32, 34);
        DOT(DR, 13, 0, 33);
    }
    if (LastMove == KEY_DOWN) {
        DOT(UR, 14, color, 23);
    } else if (LastMove == KEY_LEFT) {
        DOT(UR, 14, color, 22);
        DOT(DR, 13, 0, 31);
    } else if (LastMove == KEY_RIGHT) {
        DOT(UR, 14, color, 24);
        DOT(DR, 13, 0, 35);
    }
}

//personagem, carinha da Hudson Soft
void block::BOMBERBALL(short int color, short int backcolor, char LastMove) {
	CIRCLE(color, backcolor);
	switch(LastMove) {
        case KEY_DOWN:	DOT(VL, 0, 6, 22, 24);	DOT(NR, 6, 0, 23); break;
        case KEY_LEFT:	DOT(VL, 0, 6, 22);	DOT(NR, 6, 0, 23, 24);	break;
        case KEY_RIGHT:	DOT(NR, 6, 0, 22, 23); DOT(VL, 0, 6, 24);
	}
}

//personagem, morte
void block::BOMBERDIE() {
	CIRCLE(12, 0);
	DOT('x', 0, 15, 22, 24);
	DOT(NR, 15, 0, 23);
}

void block::BOSS(short int color) {
    ZERO();
	//e[5] = bicho
	//e[00] = bloco não vazio
	e[0] = e[5] = true;
	if (color == 12) {
	    monster = '5';
	} else if (color == 4) {
	    monster = '6';
	} else {
	    monster = '7';
	}

    CIRCLE(color, 0);
    DOT(RT, 12, 0, 22);
    DOT(NR, 0, 12, 23);
    DOT(LT, 12, 0, 24);
}

void block::HERO(short int color, char LastMove) {
    //e[0] = bloco não vazio
    //e[9] = cabeça do bomberball
    e[0] = e[9] = true;
	BOMBERBALL(color, 0, LastMove);
}

//e[5] = bicho
//e[00] = bloco não vazio
void block::MONSTER(char i) {
	switch (i) {
		case '1': MONSTER1(); break;
		case '2': MONSTER2(); break;
		case '3': MONSTER3(); break;
		case '4': MONSTER4();
	}
}

void block::MONSTER1() {
	ZERO();
	e[0] = e[5] = true;
	monster = '1';

	CIRCLE(12, 0);
	HLINE(UT, 12, 0, 1);
	DOT(E2, 0, 12, 22);
	DOT(E3, 0, 12, 24);
	DOT(UT, 0, 12, 33);
}

void block::MONSTER2() {
	ZERO();
	e[0] = e[5] = true;
	monster = '2';

	DOT(UT, 12, 0, 12, 14);
	DOT(LT, 12, 0, 21);
	DOT(E2, 0, 12, 22);
	DOT(DT, 0, 12, 23);
	DOT(E3, 0, 12, 24);
	DOT(RT, 12, 0, 25);
	DOT(NR, 12, 0, 32, 34);
	DOT(202, 0, 12, 33);
}

void block::MONSTER3() {
	ZERO();
	e[0] = e[5] = true;
	monster = '3';

	DOT(UT, 12, 0, 11, 13, 15);
	DOT(DT, 12, 0, 31, 33, 35);
	DOT(RT, 0, 12, 21);
	DOT(E2, 0, 12, 22);
	DOT(UT, 0, 12, 23);
	DOT(E3, 0, 12, 24);
	DOT(LT, 0, 12, 25);
}

void block::MONSTER4() {
	ZERO();
	e[0] = e[5] = true;
	monster = '4';

	BLOCK(NR, 12, 0);
	DOT(NR, 0, 0, 11, 15);
	DOT(DR, 12, 0, 12, 14, 21, 25);
	DOT(E2, 0, 12, 22);
	DOT(E3, 0, 12, 24);
	DOT(UT, 0, 12, 32, 34);
	DOT(SQ, 0, 12, 33);
}

//***itens/portal***
    //e[3] = item
    //e[6] = portal/fim da fase
	//e[00] = bloco não vazio

//bomb up item
void block::BOMBIT() {
	e[0] = e[3] = true;
	item = 'b';

	BOMB1(10);
}

//fire up item
void block::FIREIT() {
	e[0] = e[3] = true;
	item = 'f';

	BLOCK(NR, 12, 0);

	DOT(NR, 10, 0, 11, 15);
	DOT(DR, 12, 10, 12, 14);
	DOT(UR, 12, 14, 22, 24);
	DOT(UR, 14, 15, 23);
	DOT(UR, 12, 10, 31, 35);
	DOT(DR, 12, 14, 32, 33, 34);
}

//portão de teleport
void block::GATE() {
	e[0] = e[6] = true;

	CIRCLE(9, 0);
	DOT(LT, 11, 9, 22);
	DOT(NR, 11, 0, 23);
	DOT(RT, 11, 9, 24);
}

//invencible item
void block::INVENCIBLEIT() {
	e[0] = e[3] = true;
	item = 'i';

	BLOCK(NR, 6, 14);
	HLINE(UT, 6, 14, 1);
	DOT(LG, 2, 6, 21, 23, 25);
}

//bomb kick item
void block::KICKIT() {
    e[0] = e[3] = true;
	item = 'k';

	BLOCK(NR, 14, 0);
	DOT(NR, 15, 0, 11, 21);
	DOT(NR, 13, 0, 31, 32, 33);
	DOT(B2, 12, 14, 24, 25, 35);
	DOT(DR, 13, 14, 34);
}

//life up item/ 1up
void block::LIFEIT() {
	e[0] = e[3] = true;
	item = 'l';

	BOMBERBALL(15, 10, KEY_DOWN);
}

//bomb punch item
void block::PUNCHIT() {
    e[0] = e[3] = true;
	item = 'p';

	BLOCK(NR, 14, 0);
	VLINE(NR, 13, 0, 3);
	VLINE(B2, 12, 14, 5);
	DOT(DR, 13, 14, 14);
	DOT(NR, 15, 0, 21, 22);
	DOT(NR, 13, 0, 24);
	DOT(UR, 13, 14, 34);
}

//super bomb item
void block::SBOMBIT() {

	e[0] = e[3] = true;
	item = 'B';

	BOMB1(14);
	DOT(LT, 7, 1, 21);
	DOT(RT, 7, 1, 25);
	DOT(DT, 7, 1, 32, 34);
}

//super fire item
void block::SFIREIT() {
	e[0] = e[3] = true;
	item = 'F';

	CIRCLE(12, 14);
	DOT(NR, 14, 0, 11, 15);
	DOT(DR, 12, 14, 12, 14);
}

//time bomb item
void block::TBOMBIT() {
    e[0] = e[3] = true;
	item = 't';

    BOMB1(14);
    DOT(205, 8, 1, 12, 14);
    DOT(203, 8, 1, 13);
}

//wall cross item
void block::WALLIT() {
	e[0] = e[3] = true;
	item = 'w';

	BLOCK(SQ, 12, 14);
	VLINE('=', 12, 14, 1);
	VLINE('=', 12, 14, 2);
}
