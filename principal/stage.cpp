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
e[15] = invencible item		 invencibleit

Expandível a até e[19], por enquanto.
*/

typedef struct stage {
	//numero de bombas
	int Bomb;
	//numero do map
	int Stage;
	//hyper efeitos
	bool Effect[20];
	//poder de fogo
	int Fire;

	int Color;
	int Life;
	int Score[6];
	int Time[3];

	//cheatzors!
	char Pass[13];
	char Key;

	//225 blocos 3x5 em si no mapa
	block B[15][15];

	//bloco Memoria para movimentação
	block Memory;

	void BEGIN();
	void PRINT();
	void CONTROL(int i, int j);
	int MOVE(int i, int j);
	void ITEM(int i, int j);
	void TITLE();
	void DIE(int i, int j);

	//construindo...
	void PASSWORD();
	void EXPLOSION(int i, int j);
	void EXPLOSION2(int i, int j);
	void FIRE(int i, int j, int x);
};

void stage::BEGIN() {
	int i , j;
	Memory.ZERO();

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

	//configurações iniciais
	//3 vidas, bomba e poder de fogo em 1, tempo 5:00
	Life = 3;
	Bomb = Fire = 1;
	Time[0] = Time[1] = 0;
	Time[2] = 5;

	//zera pontuação
	for (i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	//zera entrada de cheats
	for (i = 0; i < 13; i++) {
		Pass[i] = '\0';
	}
	//zera hyper efeitos
	for(i = 0; i < 20; i++) {
		Effect[i] = false;
	}

	//bloco inquebrável?
	Effect[0] = true;

	//zera mapa
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
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

	for (i = 1; i < 14; i++) {
		for (j = 1; j < 14; j++) {
			//Boards
			if (i == 1 || j == 1|| i == 13 || j == 13) {
				B[i][j].BOARDS(Color-8);
				//e[1] = bloco inquebravel
				B[i][j].e[1] = true;
			//Blocks
			} else if (i%2 == 1 && j%2 == 1) {
				B[i][j].BLOCK(NR,Color);
				//e[1] = bloco inquebravel
				B[i][j].e[1] = 1;
			}
		}
	}

	B[2][2].BOMBERBALL(15);
	TITLE();
}

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

void stage::CONTROL(int i, int j) {
	int k;

	gotoxy(j*5+3, i*3+3);
	do {
		Key = getch();
		//se o cara apertar enter, abra o console de cheat
		if (Key == '\r') {
			PASSWORD();

		//caso apertar espaço e se não tiver morto...
		} else if ( Key == ' ' && B[i][j].e[7] == 0) {
			for (k = 0; k < 5; k++) {
				B[i][j].BOMB1();
				B[i][j].PRINT(i, j);
				//MOVE(i, j);
				sleep(200);
				B[i][j].BOMB2();
				B[i][j].PRINT(i, j);
				//MOVE(i, j);
				sleep(200);
			}
			//MOVE(i,j);
			sleep(200);
			B[i][j].e[2]=  0;
			B[i][j].e[7] = 0;
			EXPLOSION(i,j);
			Memory = B[i][j];
		// Movimento
		} else if (Key == 'd' || Key == 'a' ) {
			j = MOVE(i, j);
		} else if (Key == 's' || Key == 'w') {
			i = MOVE(i, j);
		}
	} while (Key == 'a' || Key == 's' || Key == 'd' || Key == 'w' || Key== ' ' || Key == '\r');
}

int stage::MOVE(int i, int j) {
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

	if (Effect[6] == 0) {
		if (B[i+down][j+right].e[2] == 1) {
			if (Key == 'w' || Key == 's') {
					return i;
				} else {
					return j;
				}
			}
		}

	if ((Key == 'w' && i <= 2 ) || (Key =='s' && i >= 12) || ( Key=='a' && j <= 2) || (Key=='d' && j >= 12) || (B[i+down][j+right].e[1] == 1)) {
		if (Key == 'w' || Key == 's') {
			return i;
		} else {
			return j;
		}
	} else {
		B[i][j] = Memory;
		B[i][j].PRINT(i,j);

		if (B[i+down][j+right].e[3] == 1) {
			Memory.ZERO();
			ITEM(i+down,j+right);
		} else {
			Memory = B[i+down][j+right];
		}

		if (B[i+down][j+right].e[0] == 1 && Effect[0] == 1) {
			DIE(i+down,j+right);
		} else {
			B[i+down][j+right].BOMBERBALL(15);
		}

		B[i+down][j+right].PRINT(i+down,j+right);

		if (Key == 'w' || Key == 's') {
			return (i+down);
		} else {
			return (j+right);
		}
	}
}

void stage::ITEM(int i, int j) {
	if (B[i][j].e[8] == true) {
		if (Fire < 9) {
			Fire++;
			B[0][3].NUMBER(Fire, 15);
			B[0][3].PRINT(0, 3);
		}
	} else if (B[i][j].e[9] == true) {
		if (Bomb < 9) {
			Bomb++;
			B[0][5].NUMBER(Bomb,15);
			B[0][5].PRINT(0,5);
		}
	} else if (B[i][j].e[10] == true) {
		Effect[6]=1;
		B[2][14].WALLIT(14);
		B[2][14].PRINT(2, 14);
	} else if (B[i][j].e[11] == true) {
		if (Life<9) {
			Life++;
			B[0][1].NUMBER(Life, 15);
			B[0][1].PRINT(0,1);
		}
	} else if (B[i][j].e[13] == true) {
		Effect[13] = true;
		B[4][14].SBOMBIT(14);
		B[4][14].PRINT(4, 14);
	} else if(B[i][j].e[14] == true) {
		Effect[14]  = true;
		Fire = 9;
		B[0][3].NUMBER(Fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT(14);
		B[5][14].PRINT(5,14);
	} else if (B[i][j].e[15] == true) {
		Effect[0]= false;
		B[3][14].INVENCIBLEIT(14);
		B[3][14].PRINT(3, 14);
	}
}

void stage::PASSWORD() {
	int j;
	B[14][0].LETTER('!', 12);
	B[14][0].PRINT(14, 0);

	for (j = 0; j < 13; j++) {
		Pass[j] = getch();
		if (Pass[j] != '\r') {
			B[14][j+1].LETTER(Pass[j], 15);
			B[14][j+1].PRINT(14, j+1);
		} else {
			break;
		}
	}

	B[14][0].LETTER('!', 14);
	B[14][0].PRINT(14, 0);
}

//Titulo
void stage::TITLE() {
	int i;

	B[0][0].LIFEIT(0);
	B[0][1].NUMBER(Life, 15);
	B[0][1].DOT('x', 15, 21);
	B[0][2].FIREIT(0);
	B[0][3].NUMBER(Fire, 15);
	B[0][3].DOT('x', 15, 21);
	B[0][4].BOMBIT(0);
	B[0][5].NUMBER(Bomb, 15);
	B[0][5].DOT('x', 15, 21);
	B[0][6].NUMBER(Time[2], Color);
	B[0][7].NUMBER(Time[1], Color);
	B[0][7].DOT(':', Color, 21);
	B[0][8].NUMBER(Time[0], Color);
	B[0][9].NUMBER(Score[5], 15);
	B[0][10].NUMBER(Score[4], 15);
	B[0][11].NUMBER(Score[3], 15);
	B[0][12].NUMBER(Score[2], 15);
	B[0][13].NUMBER(Score[1], 15);
	B[0][14].NUMBER(Score[0], 15);

	for (i = 0; i < 15; i++) {
		B[0][1].e[1] = true;
	}

	//Fase
	B[2][0].LETTER('S', Color);
	B[3][0].LETTER('T', Color);
	B[4][0].LETTER('A', Color);
	B[5][0].LETTER('G', Color);
	B[6][0].LETTER('E', Color);
	B[8][0].NUMBER(Stage, Color);
}

void stage::FIRE(int i, int j, int x){
	switch(x){
		case 0: B[i][j].FIRECENTER(); break;
		case 1: B[i][j].FIREHLINE(); break;
		case 2: B[i][j].FIREVLINE(); break;
		case 3: B[i][j].FIRERIGHT(); break;
		case 4: B[i][j].FIRELEFT(); break;
		case 5: B[i][j].FIREDOWN(); break;
		case 6: B[i][j].FIREUP();
	}
	B[i][j].PRINT(i,j);
}

void stage::EXPLOSION2(int i, int j) {
	int f, x, right, down;

	FIRE(i, j, 0); // center
	for (f = 1; f <= Fire; f++) {
		for (down =- f; down <= f; down += f) {
			for (right =- f; right <=f; right +=f) {
				if ((down+right == - f) || (down+right == f)) {
					if (B[i+down][j+right].e[1] == false && B[i+down][j+right].e[6] == false && B[i+down][j+right].e[7] == false) {
						if ((down == -f && i+down >= 2) || (down == f && i+down <= 12) || (right == -f && j+right >= 2) || (right == f && j+right <= 12)) {
							if (B[i+down][j+right].e[2] == true) {
								B[i+down][j+right].BLOCK(SQ, 12*16+Color);
							} else if (B[i+down][j+right].e[3] == true || B[i+down][j+right].e[5] == true) {
								B[i+down][j+right].BLOCK(NR, 12);
							} else if (B[i+down][j+right].e[4] == true) {
								EXPLOSION(i+down, j+right);
							} else {
								if (f == Fire) {
									if(down == -f) {
										x = 6; // up
									} else if (down == f) {
										x = 5; // down
									} else if (right == -f) {
										x = 4; // left
									} else {
										x = 3; // right
									}
								} else {
									if (right == 0) {
										x = 2; // vline
									} else {
										x = 1; // hline
									}
								}
							FIRE(i+down, j+right, x);
							}
						}
					}
				}
			}
		}
	}

	sleep(300);
	B[i][j].ZERO();
	B[i][j].PRINT(i,j);

	for (f = 1; f <= Fire; f++) {
		for (down =- f; down <= f; down += f) {
			for (right =- f; right <= f; right += f) {
				if ((down+right == -f ) || (down+right == f)) {
					if (B[i+down][j+right].e[2] == true || B[i+down][j+right].e[3] == true || B[i+down][j+right].e[5] == true || B[i+down][j+right].e[7] == true)
					B[i+down][j+right].ZERO();
					B[i+down][j+right].PRINT(i+down,j+right);
				}
			}
		}
	}
}

void stage::EXPLOSION(int i, int j) {
	bool up, down, left, right;
	int f;

	up = down = left = right = false;
	B[i][j].FIRECENTER();
	B[i][j].PRINT(i, j);

	for (f = 1; f <= Fire; f++) {
		//bordas
		if ((down == false) && (i+f <= 12)) {
			//bloco SQ, item, monster
			if (B[i+f][j].e[2] == true || B[i+f][j].e[3] == true || B[i+f][j].e[8] == true) {
				B[i+f][j].ZERO();
				B[i+f][j].PRINT(i+f,j);
				down = true;
			//bloco NR
			} else if (B[i+f][j].e[1] == true) {
				down = true;
			//fire
			} else if (B[i+f][j].e[7] == true) {
				//nada?
			//bomb
			} else if (B[i+f][j].e[4] == true) {
				EXPLOSION(i+f, j);
			} else {
				if (f == Fire) {
					B[i+f][j].FIREDOWN();
				} else {
					B[i+f][j].FIREVLINE();
				}
				B[i+f][j].PRINT(i+f, j);
			}
		}

		if ((up == false) && (i-f >= 2)) {
			if (B[i-f][j].e[2] == true || B[i-f][j].e[3] == true || B[i-f][j].e[8] == true) {
				B[i-f][j].ZERO();
				B[i-f][j].PRINT(i-f, j);
				up = true;
			} else if (B[i-f][j].e[1] == true) {
				up = true;
			} else if (B[i-f][j].e[7] == true) {
				//nada
			} else if (B[i-f][j].e[4] == true) {
				EXPLOSION(i-f, j);
			} else {
				if (f == Fire) {
					B[i-f][j].FIREUP();
				} else {
					B[i-f][j].FIREVLINE();
				}
			B[i-f][j].PRINT(i-f, j);
			}
		}

		if ((right == false) && (j+f <= 12)) {
			if (B[i][j+f].e[2] == true || B[i][j+f].e[3] == true || B[i][j+f].e[8] == true) {
				B[i][j+f].ZERO();
				B[i][j+f].PRINT(i, j+f);
				right = true;
			} else if (B[i][j+f].e[1] == true) {
				right = true;
			} else if (B[i][j+f].e[7] == true) {
				//nada
			} else if (B[i][j+f].e[4] == true) {
				EXPLOSION(i,j+f);
			} else {
				if (f == Fire) {
					B[i][j+f].FIRERIGHT();
				} else {
					B[i][j+f].FIREHLINE();
				}
				B[i][j+f].PRINT(i,j+f);
			}
		}

		if ((left == false) && (j-f >= 2)) {
			if (B[i][j-f].e[2] == true || B[i][j-f].e[3] == true || B[i][j-f].e[8] == true) {
				B[i][j-f].ZERO();
				B[i][j-f].PRINT(i, j-f);
				left = true;
			} else if (B[i][j-f].e[1] == true) {
				left = true;
			} else if (B[i][j-f].e[7] == true) {
				//nada
			} else if (B[i][j-f].e[4] == true) {
				EXPLOSION(i, j-f);
			} else {
				if (f == Fire) {
					B[i][j-f].FIRELEFT();
				} else {
					B[i][j-f].FIREHLINE();
				}
				B[i][j-f].PRINT(i, j-f);
			}
		}
	}

	sleep(300);
	B[i][j].ZERO();
	B[i][j].PRINT(i, j);

	for (f = 1; f <= Fire; f++) {
		for (int down =- f; down <= f; down += f) {
			for (int right =- f; right <= f; right += f) {
				if ((down+right ==- f) || (down+right == f)) {
					if (B[i+down][j+right].e[7] == true) {
						B[i+down][j+right].ZERO();
					}
					B[i+down][j+right].PRINT(i+down,j+right);
				}
			}
		}
	}
}

void stage::DIE(int i, int j) {
	B[i][j].BOMBERDIE();
	if (Life > 0) {
		Life--;
		B[0][1].NUMBER(Life, 15);
		B[0][1].PRINT(0, 1);
	}
}
