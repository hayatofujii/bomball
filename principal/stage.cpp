/*
====  ROADMAP block.e====
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
e[12] = timebomb item			tbombit***
e[13] = superbomb item			sbombit
e[14] = superfire item			sfireit
e[15] = invencible item		    invencibleit
e[16] = bomberball              bomberball

Expandível a até e[19], por enquanto.
*/

typedef struct bomb {
    clock_t start[9]; //início de cada bomba
    int total; // total de bombas disponíveis
    int inboard; // bombas no tabuleiro
    int line[9], column[9]; // coordenadas de cada bomba
    int framenumber[9]; // frame que será executado para cada bomba
    int fire; //potência do fogo
};

typedef struct stage {

	//bomba
	bomb Bomb;

	//tempos
	clock_t StartTime;
	int TotalTime;

	//endereço do char
	int BomberballLine, BomberballColumn;

	//numero do map
	int Stage;
	int ActualStage; //para level up

	//hyper efeitos
	bool InvencibleMode;
	bool WallCrossMode;
	bool SuperBombMode;
	bool SuperFireMode;

	int Color;
	int Life;

	//pontuações
	int Point;
	int Score[6];

	//tempo para ser exibido
	int Time[3];

	//cheatzors!
	char Pass[14];
	char Key;

	//225 blocos 3x5 em si no mapa
	block B[15][15];

	//bloco Memoria para movimentação
	block Memory;

	void BEGIN();
	void STAGE();
	void GAME();
	void PRINT();
	void CONTROL();
	void MOVE();
	void ITEM(int i, int j);
	void DIE(int i, int j);
	void FIREREMOVE();
	void SCORE(int i, int j);

	//construindo...
	void PASSWORD();
	void EXPLOSION();
	void BOMB();
	void TIME();
};

void stage::BEGIN() {
	int i , j;

	Stage = ActualStage = 1; //inicia o stage 1

	//configurações iniciais
	//3 vidas, bomba e poder de fogo em 1, tempo 5:00
	Life = 3;
	Bomb.total = Bomb.fire = 1;

	//zera pontuação
	for (i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	Point = 0;

	//zera hyper efeitos
	WallCrossMode = false;
	SuperBombMode = false;
	SuperFireMode = false;
	InvencibleMode = false;

	//zera mapa
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			B[i][j].ZERO();
		}
	}

	B[0][0].LIFEIT(0);// bomberball
	B[0][1].DOT('x', 15, 21);

	B[0][2].FIREIT(0); // fogo
	B[0][3].DOT('x', 15, 21);

	B[0][4].BOMBIT(0);// bomba
	B[0][5].DOT('x', 15, 21);

	//cheatzor
	B[14][0].LETTER('!',15);
}

void stage::GAME() {
    int i, j;

    //posição inicial (2, 2)
	BomberballLine = BomberballColumn = 2;

    Time[0] = 5;// 5 minutos
	Time[1] = Time[2] = 0;

	Memory.ZERO();// zera memória

	Bomb.inboard = 0; //sem bombas no tabuleiro

	//zera entrada de cheats
	for (i = 0; i < 14; i++) {
		Pass[i] = '\0';
	}

	for (i = 1; i < 14; i++) {
		for (j = 1; j < 14; j++) {
			//Boards
			if (i == 1 || j == 1|| i == 13 || j == 13) {
				B[i][j].BOARDS(Color-8);
				//e[1] = bloco inquebravel
				//B[i][j].e[1] = true;
			//Blocks
			} else if (i%2 == 1 && j%2 == 1) {
				B[i][j].BLOCK(NR, Color);
				//e[1] = bloco inquebravel
				B[i][j].e[1] = true;
			}
		}
	}

	B[2][2].BOMBERBALL(15);//bomberball

	B[0][1].NUMBER(Life, 15);// numero life
	B[0][3].NUMBER(Bomb.fire, 15);// numero fire
	B[0][5].NUMBER(Bomb.total, 15);// numero bomb

	B[0][6].NUMBER(Time[0], Color);//tempo
	B[0][7].NUMBER(Time[1], Color);
	B[0][7].DOT(':', Color, 21);
	B[0][8].NUMBER(Time[2], Color);

	B[0][9].NUMBER(Score[0], 15);//score
	B[0][10].NUMBER(Score[1], 15);
	B[0][11].NUMBER(Score[2], 15);
	B[0][12].NUMBER(Score[3], 15);
	B[0][13].NUMBER(Score[4], 15);
	B[0][14].NUMBER(Score[5], 15);

	//Fase
	B[2][0].LETTER('S', Color);
	B[3][0].LETTER('T', Color);
	B[4][0].LETTER('A', Color);
	B[5][0].LETTER('G', Color);
	B[6][0].LETTER('E', Color);
	B[8][0].NUMBER(Stage, Color);

	//tabuleiro, para teste
	B[2][3].FIREIT(10);
	B[2][5].FIREIT(10);
	B[2][7].FIREIT(10);
	B[2][9].MONSTER();
	B[2][11].BOMBIT(10);
	B[3][2].BOMBIT(10);
	B[4][5].SFIREIT(14);
	B[5][2].LIFEIT(10);
	B[7][2].WALLIT(14);
	B[9][2].INVENCIBLEIT(14);
	B[11][2].SBOMBIT(14);
	B[12][12].GATE();

	B[6][3].FIREIT(10);
	B[6][5].FIREIT(10);
	B[6][7].FIREIT(10);
	B[6][9].FIREIT(10);
	B[6][11].FIREIT(10);

	PRINT();

	gotoxy(1,50);
	textcolor(15);
	printf("\nPressione:\nW/A/S/D para mover\nSPACE para soltar bomba\nOUTRA tecla para sair");

	//iguala start time a hora atual
	StartTime = clock();
	//duração de cada map: 5 minutos (em segundos)
	TotalTime = 5*60;

	//entrada de controles, enquanto tiver vivo
	while (Stage == ActualStage) {
		//limpa buffer teclado
		rewind (stdin);

		//se nenhuma tecla for apertada
		if (!kbhit()) {
			 //se houver bombas no tabuleiro
			if (Bomb.inboard > 0) {
				// se passar a duração de um frame de 0,2 segundos
				if(clock() - Bomb.start[0] >= 0.2 * CLOCKS_PER_SEC) {
					BOMB();
				}
			}

			//se a diferença entre a hora atual e do começo do jogo for maior ou igual a 1 segundo
			if (clock() - StartTime >= 1 * CLOCKS_PER_SEC) {
				//imprima o relógio
				TIME();
			}
		}
		else {
			CONTROL();
		}
	}
}

void stage::STAGE() {
    int i, j;

    //ugh, pallete swaps
	if (Stage == 1) {
		Color = 11;
	} else if (Stage == 2) {
		Color = 10;
	} else if (Stage == 3) {
		Color = 14;
	} else if (Stage == 4) {
		Color = 13;
	} else if (Stage == 5) {
		Color = 12;
	}

    for (i = 2; i < 13; i++) {// zera o tabuleiro central
        for (j = 2; j < 13; j++) {
            B[i][j].ZERO();
        }
    }

    //tabuleiros
	if (Stage == 1) {
		for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i%2 == 0 && j%2 == 0) {
					B[i][j].BLOCK(SQ, Color);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
				}
			}
		}
	} else if (Stage == 2) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (i%2 == 1) {
					B[i][j].BLOCK(SQ, Color);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
				}
			}
		}
	} else if (Stage == 3) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (j%2 == 1) {
					B[i][j].BLOCK(SQ, Color);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
				}
			}
		}
	} else if (Stage == 4) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if ((i%2 == 1 && i != 7) || (j%2 == 1 && j != 7)) {
					B[i][j].BLOCK(SQ, Color);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
				}
			}
		}
	}
}

//imprima uma linha
void stage::PRINT() {
	int i, j, x;
	for (i = 0; i < 15; i++) {
		for (x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (j = 0; j < 15; j++) {
				B[i][j].PRINTLINE(x);
			}
			printf("\n");
		}
	}
}

//controles
void stage::CONTROL() {
	gotoxy(BomberballColumn*5+3, BomberballLine*3+3);
	Key = getch();

	//se o cara apertar enter, abra o console de cheat
	if (Key == '\r') {
		PASSWORD();

	//caso apertar espaço e se não tiver morto...
	} else if ( Key == ' ' && B[BomberballLine][BomberballColumn].e[7] == false) {
		Bomb.line[0] = BomberballLine;
		Bomb.column[0] = BomberballColumn;
		Bomb.framenumber[0] = 1;
		Bomb.start[0] = clock();
		Bomb.inboard += 1;
		BOMB();

	//caso apertar botões de movimento
	} else if (Key == 'd' || Key == 'a' || Key == 's' || Key == 'w') {
		MOVE();
	}
}


//movimentação
void stage::MOVE() {
	int down, right;
	down = right = 0;

	if (Key =='w' ) {
		down = -1;
	} else if (Key == 's') {
		down = 1;
	} else if (Key == 'a') {
		right = -1;
	} else if (Key == 'd') {
		right = 1;
	}

	if (WallCrossMode == true || (WallCrossMode == false && B[BomberballLine+down][BomberballColumn+right].e[2] == false)) {
		if((Key == 'w' && BomberballLine > 2 ) || (Key == 's' && BomberballLine < 12) || (Key== 'a' && BomberballColumn > 2) || (Key== 'd' && BomberballColumn < 12)) {
			//se for portal
			if (B[BomberballLine+down][BomberballColumn+right].e[6] == true) {
			    ActualStage++;
			//se não for bloco quebrável
			} else if (B[BomberballLine+down][BomberballColumn+right].e[1] == false) {
				B[BomberballLine][BomberballColumn] = Memory;
				B[BomberballLine][BomberballColumn].PRINT(BomberballLine,BomberballColumn);

				if (B[BomberballLine+down][BomberballColumn+right].e[3] == true) {
					Memory.ZERO();
					ITEM(BomberballLine+down,BomberballColumn+right);
				} else {
					Memory = B[BomberballLine+down][BomberballColumn+right];
				}

				if (B[BomberballLine+down][BomberballColumn+right].e[0] == true && InvencibleMode == false) {
					DIE(BomberballLine+down,BomberballColumn+right);
				} else {
					B[BomberballLine+down][BomberballColumn+right].BOMBERBALL(15);
				}

				B[BomberballLine+down][BomberballColumn+right].PRINT(BomberballLine+down, BomberballColumn+right);

				if (Key == 'w' || Key == 's') {
					BomberballLine += down;
				} else {
					BomberballColumn += right;
				}
			}
		}
	}
}

//efeitos dos items
void stage::ITEM(int i, int j) {
	if (B[i][j].e[8] == true) {
		if (Bomb.fire < 9) {
			Bomb.fire++;
			B[0][3].NUMBER(Bomb.fire, 15);
			B[0][3].PRINT(0, 3);
		}
	} else if (B[i][j].e[9] == true) {
		if (Bomb.total < 9) {
			Bomb.total++;
			B[0][5].NUMBER(Bomb.total,15);
			B[0][5].PRINT(0,5);
		}
	} else if (B[i][j].e[10] == true) {
		WallCrossMode = true;
		B[2][14].WALLIT(14);
		B[2][14].PRINT(2, 14);
	} else if (B[i][j].e[11] == true) {
		if (Life<9) {
			Life++;
			B[0][1].NUMBER(Life, 15);
			B[0][1].PRINT(0,1);
		}
	} else if (B[i][j].e[13] == true) {
		SuperBombMode = true;
		B[4][14].SBOMBIT(14);
		B[4][14].PRINT(4, 14);
	} else if(B[i][j].e[14] == true) {
		SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT(14);
		B[5][14].PRINT(5,14);
	} else if (B[i][j].e[15] == true) {
		InvencibleMode = true;
		B[3][14].INVENCIBLEIT(14);
		B[3][14].PRINT(3, 14);
	}
}

//entrada de cheats
void stage::PASSWORD() {
	int j;

	B[14][0].LETTER('!', 12);
	B[14][0].PRINT(14, 0);

	for (j = 0; j < 14; j++) {
		Pass[j] = getch();
		if (Pass[j] != '\r') {
			B[14][j+1].LETTER(Pass[j], 15);
			B[14][j+1].PRINT(14, j+1);
		} else {
			break;
		}
	}
	if (Pass[0] == 'i' && Pass[1] == 'n' && Pass[2] == 'v' && Pass[3] == 'e' && Pass[4] == 'n' && Pass[5] == 'c' && Pass[6] == 'i'&& Pass[7] == 'b'&& Pass[8] == 'l'&& Pass[9] == 'e' ) {
	    InvencibleMode = true;
		B[3][14].INVENCIBLEIT(14);
		B[3][14].PRINT(3, 14);
	} else if (Pass[0] == 's' && Pass[1] == 'u' && Pass[2] == 'p' && Pass[3] == 'e' && Pass[4] == 'r' && Pass[5] == 'b' && Pass[6] == 'o'&& Pass[7] == 'm'&& Pass[8] == 'b') {
	    SuperBombMode = true;
		B[4][14].SBOMBIT(14);
		B[4][14].PRINT(4, 14);
	}
	else if (Pass[0] == 'w' && Pass[1] == 'a' && Pass[2] == 'l' && Pass[3] == 'l' && Pass[4] == 'c' && Pass[5] == 'r' && Pass[6] == 'o'&& Pass[7] == 's'&& Pass[8] == 's') {
	    WallCrossMode = true;
		B[2][14].WALLIT(14);
		B[2][14].PRINT(2, 14);
	}
	else if (Pass[0] == 's' && Pass[1] == 'u' && Pass[2] == 'p' && Pass[3] == 'e' && Pass[4] == 'r' && Pass[5] == 'f' && Pass[6] == 'i'&& Pass[7] == 'r'&& Pass[8] == 'e') {
	    SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT(14);
		B[5][14].PRINT(5,14);
	}
	B[14][0].LETTER('!', 14);
	B[14][0].PRINT(14, 0);
}

void stage::EXPLOSION() {
	int f;
	bool down, up, left, right;

	down = up = right = left = false;
	B[Bomb.line[0]][Bomb.column[0]].FIRECENTER();
	B[Bomb.line[0]][Bomb.column[0]].PRINT(Bomb.line[0], Bomb.column[0]);

	// aumenta a extensão da bomba
	for (f = 1; f <= Bomb.fire; f++) {
		//cima
		if (B[Bomb.line[0]-f][Bomb.column[0]].e[1] == true) {
			up = true;
			// não coloque sobre portal ou fogo
		} else if (B[Bomb.line[0]-f][Bomb.column[0]].e[6] == false && B[Bomb.line[0]-f][Bomb.column[0]].e[7] == false) {
			// não imprime nas bordas e não atravessa blocos
			// O BUG TEM QUE ESTAR AQUI E NAS 3 OUTRAS ITERAÇÕES!
			if (up == false) {
				if (B[Bomb.line[0]-f][Bomb.column[0]].e[2] == true || B[Bomb.line[0]-f][Bomb.column[0]].e[3] == true || B[Bomb.line[0]-f][Bomb.column[0]].e[5] == true) { // blocos quebráveis, itens e monsters
					B[Bomb.line[0]-f][Bomb.column[0]].BLOCK(NR, 12);
					B[Bomb.line[0]-f][Bomb.column[0]].e[7] = true;
					SCORE(Bomb.line[0]-f, Bomb.column[0]);

					// se a superbombmode não estiver ativada
					if (SuperBombMode == false) {
						up = true;
					}
				//outra bomba chama a função recursivamente, se é que vai ter.
				} else if (B[Bomb.line[0]-f][Bomb.column[0]].e[4] == true) {
					EXPLOSION();
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[0]-f][Bomb.column[0]].FIREUP();
					} else {
						B[Bomb.line[0]-f][Bomb.column[0]].FIREVLINE();
					}
				}
				B[Bomb.line[0]-f][Bomb.column[0]].PRINT(Bomb.line[0]-f, Bomb.column[0]);
			}
		}

		// baixo
		if (B[Bomb.line[0]+f][Bomb.column[0]].e[1] == true) {
			down = true;
		} else if (B[Bomb.line[0]+f][Bomb.column[0]].e[6] == false && B[Bomb.line[0]+f][Bomb.column[0]].e[7] == false) {
			if (down == false) {
				if (B[Bomb.line[0]+f][Bomb.column[0]].e[2] == true || B[Bomb.line[0]+f][Bomb.column[0]].e[3] == true || B[Bomb.line[0]+f][Bomb.column[0]].e[5] == true) {
					B[Bomb.line[0]+f][Bomb.column[0]].BLOCK(NR, 12);
					B[Bomb.line[0]+f][Bomb.column[0]].e[7] = true;
					SCORE(Bomb.line[0]+f, Bomb.column[0]);
					if (SuperBombMode == false) {
						down = true;
					}
				} else if (B[Bomb.line[0]+f][Bomb.column[0]].e[4] == true) {
					EXPLOSION();
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[0]+f][Bomb.column[0]].FIREDOWN();
					} else {
						B[Bomb.line[0]+f][Bomb.column[0]].FIREVLINE();
					}
				}
				B[Bomb.line[0]+f][Bomb.column[0]].PRINT(Bomb.line[0]+f, Bomb.column[0]);
			}
		}

		// esq.
		if (B[Bomb.line[0]][Bomb.column[0]-f].e[1] == true) {
			left = true;
		} else if (B[Bomb.line[0]][Bomb.column[0]-f].e[6] == false && B[Bomb.line[0]][Bomb.column[0]-f].e[7] == false) {
			if (left == false) {
				if (B[Bomb.line[0]][Bomb.column[0]-f].e[2] == true || B[Bomb.line[0]][Bomb.column[0]-f].e[3] == true || B[Bomb.line[0]][Bomb.column[0]-f].e[5] == true) {
					B[Bomb.line[0]][Bomb.column[0]-f].BLOCK(NR, 12);
					B[Bomb.line[0]][Bomb.column[0]-f].e[7] = true;
					SCORE(Bomb.line[0], Bomb.column[0]-f);
					if (SuperBombMode == false) {
						left = true;
					}
				} else if (B[Bomb.line[0]][Bomb.column[0]-f].e[4] == true) {
					EXPLOSION();
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[0]][Bomb.column[0]-f].FIRELEFT();
					} else {
						B[Bomb.line[0]][Bomb.column[0]-f].FIREHLINE();
					}
				}
				B[Bomb.line[0]][Bomb.column[0]-f].PRINT(Bomb.line[0], Bomb.column[0]-f);
			}
		}

		//direita
		if (B[Bomb.line[0]][Bomb.column[0]+f].e[1] == true) {
			right = true;
		} else if (B[Bomb.line[0]][Bomb.column[0]+f].e[6] == false && B[Bomb.line[0]][Bomb.column[0]+f].e[7] == false) {
			if (right == false) {
				if (B[Bomb.line[0]][Bomb.column[0]+f].e[2] == true || B[Bomb.line[0]][Bomb.column[0]+f].e[3] == true || B[Bomb.line[0]][Bomb.column[0]+f].e[5] == true) {
					B[Bomb.line[0]][Bomb.column[0]+f].BLOCK(NR, 12);
					B[Bomb.line[0]][Bomb.column[0]+f].e[7] = true;
					SCORE(Bomb.line[0], Bomb.column[0]+f);
					if (SuperBombMode == false) {
						right = true;
					}
				} else if (B[Bomb.line[0]][Bomb.column[0]+f].e[4] == true) {
					EXPLOSION();
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[0]][Bomb.column[0]+f].FIRERIGHT();
					} else {
						B[Bomb.line[0]][Bomb.column[0]+f].FIREHLINE();
					}
				}
				B[Bomb.line[0]][Bomb.column[0]+f].PRINT(Bomb.line[0], Bomb.column[0]+f);
			}
		}
	}
}

//desenhos do fogo, reto
void stage::FIREREMOVE() {
	int f;

	for (f = 1;f <= Bomb.fire; f++) {
		//para cima
		if (B[Bomb.line[0]-f][Bomb.column[0]].e[7] == true && Bomb.line[0]-f >= 2) {
			B[Bomb.line[0]-f][Bomb.column[0]].ZERO();
			B[Bomb.line[0]-f][Bomb.column[0]].PRINT(Bomb.line[0]-f, Bomb.column[0]);
		}
		//baixo
		if (B[Bomb.line[0]+f][Bomb.column[0]].e[7] == true && Bomb.line[0]+f <= 12) {
			B[Bomb.line[0]+f][Bomb.column[0]].ZERO();
			B[Bomb.line[0]+f][Bomb.column[0]].PRINT(Bomb.line[0]+f, Bomb.column[0]);
		}
		//esq.
		if (B[Bomb.line[0]][Bomb.column[0]-f].e[7] == true && Bomb.column[0]-f >= 2) {
			B[Bomb.line[0]][Bomb.column[0]-f].ZERO();
			B[Bomb.line[0]][Bomb.column[0]-f].PRINT(Bomb.line[0], Bomb.column[0]-f);
		}
		//direita
		if (B[Bomb.line[0]][Bomb.column[0]+f].e[7] == true && Bomb.column[0]+f <= 12) {
			B[Bomb.line[0]][Bomb.column[0]+f].ZERO();
			B[Bomb.line[0]][Bomb.column[0]+f].PRINT(Bomb.line[0], Bomb.column[0]+f);
		}
	}
	//centro de explosão
	B[Bomb.line[0]][Bomb.column[0]].ZERO();
	B[Bomb.line[0]][Bomb.column[0]].PRINT(Bomb.line[0], Bomb.column[0]);
}

//calcula pontuação
//aproveita e já imprime-a
void stage::SCORE(int i, int j) {
	int k;

	//10 pontos por estourar uma parede
	if (B[i][j].e[2] == true) {
		Point += 10;
	}
	//100 pontos por estourar um bicho
	else if (B[i][j].e[5] == true) {
		Point += 100;
	}

	Score[0] = (Point % 1000000)/100000;
	Score[1] = (Point % 0100000)/010000;
	Score[2] = (Point % 0010000)/001000;
	Score[3] = (Point % 0001000)/000100;
	Score[4] = (Point % 0000100)/000010;
	Score[5] = Point % 10;

	for (k = 0; k < 6; k++) {
		B[0][k+9].NUMBER(Score[k], 15);
		B[0][k+9].PRINT(0, k+9);
	}
}

//morte do bomberman
//aproveita e já imprime o numero de vidas restantes
void stage::DIE(int i, int j) {
	B[i][j].BOMBERDIE();
	if (Life > 0) {
		Life--;
		B[0][1].NUMBER(Life, 15);
		B[0][1].PRINT(0, 1);
	}
}

//imprime estados da bomba
void stage::BOMB() {
	if (Bomb.framenumber[0] == 11) {
		EXPLOSION();
	} else if (Bomb.framenumber[0] == 12) {
		FIREREMOVE();
		Bomb.inboard = 0;
	} else if (Bomb.framenumber[0] % 2 == 1) {
		B[Bomb.line[0]][Bomb.column[0]].BOMB1();
		B[Bomb.line[0]][Bomb.column[0]].PRINT(Bomb.line[0], Bomb.column[0]);
	} else {
		B[Bomb.line[0]][Bomb.column[0]].BOMB2();
		B[Bomb.line[0]][Bomb.column[0]].PRINT(Bomb.line[0], Bomb.column[0]);
	}
	//Bomb.frametime[0] += 0.2;
	Bomb.start[0] = clock();
	Bomb.framenumber[0] += 1;
}

//imprime o relógio
void stage::TIME() {
	int i;

	TotalTime--;
	if (TotalTime >= 0) {
		//minutos
		Time[0] = TotalTime/60;
		//segundos dezenas
		Time[1] = (TotalTime%60)/10;
		//segundos unidades
		Time[2] = TotalTime%10;

		//imprima os numeros
		for (i = 0; i < 3; i++) {
			B[0][i+6].NUMBER(Time[i], Color);
			B[0][i+6].PRINT(0,i+6);
		}
		StartTime = time(NULL);
	}
}

