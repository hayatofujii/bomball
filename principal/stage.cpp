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

Expand�vel a at� e[19], por enquanto.
*/

typedef struct stage {
	time_t BombStart, StartTime;

	int TotalTime;

	double FrameTime;
	int BombFrame;
	int BombLine;
	int BombColumn;
	bool BombInBoard;

	int BomberballLine, BomberballColumn;

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
	int Point; // score point
	int Time[3];

	//cheatzors!
	char Pass[14];
	char Key;

	//225 blocos 3x5 em si no mapa
	block B[15][15];

	//bloco Memoria para movimenta��o
	block Memory;

	void BEGIN();
	void PRINT();
	void CONTROL();
	void MOVE();
	void ITEM(int i, int j);
	void TITLE();
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

	//configura��es iniciais
	//3 vidas, bomba e poder de fogo em 1, tempo 5:00
	Life = 3;
	Bomb = Fire = 1;
	Time[0] = 5;
	Time[1] = Time[2] = 0;

	BombInBoard = false; //sem bombas no tabuleiro

	//zera pontua��o
	for (i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	Point = 0;
	//zera entrada de cheats
	for (i = 0; i < 14; i++) {
		Pass[i] = '\0';
	}
	//zera hyper efeitos
	for(i = 0; i < 20; i++) {
		Effect[i] = false;
	}

	//invencibilidade = false
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
				//B[i][j].e[1] = true;
			//Blocks
			} else if (i%2 == 1 && j%2 == 1) {
				B[i][j].BLOCK(NR, Color);
				//e[1] = bloco inquebravel
				B[i][j].e[1] = true;
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

void stage::CONTROL() {
	gotoxy(BomberballColumn*5+3, BomberballLine*3+3);
	Key = getch();

    //se o cara apertar enter, abra o console de cheat
        if (Key == '\r') {
            PASSWORD();

        //caso apertar espa�o e se n�o tiver morto...
        } else if ( Key == ' ' && B[BomberballLine][BomberballColumn].e[7] == false) {
            BombLine = BomberballLine;
            BombColumn = BomberballColumn;
            BombFrame = 1;
            BombStart = time(NULL);
            BombInBoard = true;
            FrameTime = 0.2;//0,2 segundos cada frame
            BOMB();
        } else if (Key == 'd' || Key == 'a' || Key == 's' || Key == 'w') {
            MOVE();
        }
}


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

	if (Effect[10] == true || (Effect[10] == false && B[BomberballLine+down][BomberballColumn+right].e[2] == false)) {
        if((Key == 'w' && BomberballLine > 2 ) || (Key == 's' && BomberballLine < 12) || (Key== 'a' && BomberballColumn > 2) || (Key== 'd' && BomberballColumn < 12)) {
            if (B[BomberballLine+down][BomberballColumn+right].e[1] == false) { //se n�o for bloco inquebr�vel
                B[BomberballLine][BomberballColumn] = Memory;
                B[BomberballLine][BomberballColumn].PRINT(BomberballLine,BomberballColumn);

                if (B[BomberballLine+down][BomberballColumn+right].e[3] == true) {
                    Memory.ZERO();
                    ITEM(BomberballLine+down,BomberballColumn+right);
                } else {
                    Memory = B[BomberballLine+down][BomberballColumn+right];
                }

                if (B[BomberballLine+down][BomberballColumn+right].e[0] == true && Effect[0] == true) {
                    DIE(BomberballLine+down,BomberballColumn+right);
                } else {
                    B[BomberballLine+down][BomberballColumn+right].BOMBERBALL(15);
                }
                B[BomberballLine+down][BomberballColumn+right].PRINT(BomberballLine+down,BomberballColumn+right);
                if (Key == 'w' || Key == 's') {
                    BomberballLine += down;
                } else {
                    BomberballColumn += right;
                }
            }
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
		Effect[10] = true;
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
		Effect[14] = true;
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

	for (j = 0; j < 14; j++) {
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
	B[0][6].NUMBER(Time[0], Color);
	B[0][7].NUMBER(Time[1], Color);
	B[0][7].DOT(':', Color, 21);
	B[0][8].NUMBER(Time[2], Color);
	B[0][9].NUMBER(Score[0], 15);
	B[0][10].NUMBER(Score[1], 15);
	B[0][11].NUMBER(Score[2], 15);
	B[0][12].NUMBER(Score[3], 15);
	B[0][13].NUMBER(Score[4], 15);
	B[0][14].NUMBER(Score[5], 15);

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

void stage::EXPLOSION() {
	int f;
	bool down, up, left, right;

	down = up = right = left = false;
	B[BombLine][BombColumn].FIRECENTER();
	B[BombLine][BombColumn].PRINT(BombLine, BombColumn);
	for (f = 1; f <= Fire; f++) { // aumenta a extens�o da bomba
        if (B[BombLine-f][BombColumn].e[1] == true) {//up
            up = true;
		} else if (B[BombLine-f][BombColumn].e[6] == false && B[BombLine-f][BombColumn].e[7] == false) { // n�o BombLinemprBombLineme sobre portal ou fogo
            if (up == false) { // n�o imprime nas bordas e n�o atravessa blocos
                if (B[BombLine-f][BombColumn].e[2] == true || B[BombLine-f][BombColumn].e[3] == true || B[BombLine-f][BombColumn].e[5] == true) { // blocos quebr�veis, itens e monsters
                    B[BombLine-f][BombColumn].BLOCK(NR, 12);
                    B[BombLine-f][BombColumn].e[7] = true;
                    SCORE(BombLine-f, BombColumn);
                    if(Effect[13] == false) { // se a superbombitem n�o estiver ativada
                        up = true;
                    }
                } else if (B[BombLine-f][BombColumn].e[4] == true) { // outra bomba chama a fun��o recursivamente
                    EXPLOSION();
                } else {
                    if (f == Fire) {
                        B[BombLine-f][BombColumn].FIREUP();
                    } else {
                        B[BombLine-f][BombColumn].FIREVLINE();
                    }
                }
                B[BombLine-f][BombColumn].PRINT(BombLine-f, BombColumn);
            }
        }
        //
		if (B[BombLine+f][BombColumn].e[1] == true) {//down
            down = true;
		} else if (B[BombLine+f][BombColumn].e[6] == false && B[BombLine+f][BombColumn].e[7] == false) {
		    if (down == false) {
                if (B[BombLine+f][BombColumn].e[2] == true || B[BombLine+f][BombColumn].e[3] == true || B[BombLine+f][BombColumn].e[5] == true) {
                    B[BombLine+f][BombColumn].BLOCK(NR, 12);
                    B[BombLine+f][BombColumn].e[7] = true;
                    SCORE(BombLine+f, BombColumn);
                    if(Effect[13] == false) {
                        down = true;
                    }
                } else if (B[BombLine+f][BombColumn].e[4] == true) {
                    EXPLOSION();
                } else {
                    if (f == Fire) {
                        B[BombLine+f][BombColumn].FIREDOWN();
                    } else {
                        B[BombLine+f][BombColumn].FIREVLINE();
                    }
                }
                B[BombLine+f][BombColumn].PRINT(BombLine+f, BombColumn);
            }
        }
		//
		if (B[BombLine][BombColumn-f].e[1] == true) {//left
            left = true;
		} else if (B[BombLine][BombColumn-f].e[6] == false && B[BombLine][BombColumn-f].e[7] == false) {
            if (left == false) {
                if (B[BombLine][BombColumn-f].e[2] == true || B[BombLine][BombColumn-f].e[3] == true || B[BombLine][BombColumn-f].e[5] == true) {
                    B[BombLine][BombColumn-f].BLOCK(NR, 12);
                    B[BombLine][BombColumn-f].e[7] = true;
                    SCORE(BombLine, BombColumn-f);
                    if(Effect[13] == false) {
                        left = true;
                    }
                } else if (B[BombLine][BombColumn-f].e[4] == true) {
                    EXPLOSION();
                } else {
                    if (f == Fire) {
                        B[BombLine][BombColumn-f].FIRELEFT();
                    } else {
                        B[BombLine][BombColumn-f].FIREHLINE();
                    }
                }
                B[BombLine][BombColumn-f].PRINT(BombLine, BombColumn-f);
            }
        }
        //
		if (B[BombLine][BombColumn+f].e[1] == true) {//rBombLineght
            right = true;
		} else if (B[BombLine][BombColumn+f].e[6] == false && B[BombLine][BombColumn+f].e[7] == false) {
		    if (right == false) {
                if (B[BombLine][BombColumn+f].e[2] == true || B[BombLine][BombColumn+f].e[3] == true || B[BombLine][BombColumn+f].e[5] == true) {
                    B[BombLine][BombColumn+f].BLOCK(NR, 12);
                    B[BombLine][BombColumn+f].e[7] = true;
                    SCORE(BombLine, BombColumn+f);
                    if(Effect[13] == false) {
                        right = true;
                    }
                } else if (B[BombLine][BombColumn+f].e[4] == true) {
                    EXPLOSION();
                } else {
                    if (f == Fire) {
                        B[BombLine][BombColumn+f].FIRERIGHT();
                    } else {
                        B[BombLine][BombColumn+f].FIREHLINE();
                    }
                }
                B[BombLine][BombColumn+f].PRINT(BombLine, BombColumn+f);
            }
        }
	}
}

void stage::FIREREMOVE() {
    int f;

    for (f = 1;f <= Fire; f++) {
        if (B[BombLine-f][BombColumn].e[7] == true && BombLine-f >= 2) { //up
            B[BombLine-f][BombColumn].ZERO();
            B[BombLine-f][BombColumn].PRINT(BombLine-f, BombColumn);
        }
        if (B[BombLine+f][BombColumn].e[7] == true && BombLine+f <= 12) { //down
            B[BombLine+f][BombColumn].ZERO();
            B[BombLine+f][BombColumn].PRINT(BombLine+f, BombColumn);
        }
        if (B[BombLine][BombColumn-f].e[7] == true && BombColumn-f >= 2) { //left
            B[BombLine][BombColumn-f].ZERO();
            B[BombLine][BombColumn-f].PRINT(BombLine, BombColumn-f);
        }
        if (B[BombLine][BombColumn+f].e[7] == true && BombColumn+f <= 12) { //right
            B[BombLine][BombColumn+f].ZERO();
            B[BombLine][BombColumn+f].PRINT(BombLine, BombColumn+f);
        }
    }
    B[BombLine][BombColumn].ZERO(); // center
    B[BombLine][BombColumn].PRINT(BombLine, BombColumn);
}

void stage::SCORE(int i, int j) {
    int k;
    if (B[i][j].e[2] == true) {
        Point= Point+10;
    }
    else if (B[i][j].e[5] == true) {
        Point= Point+100;
    }
    Score[0] = (Point % 1000000) /100000;
    Score[1] = (Point % 100000) /10000;
    Score[2] = (Point % 10000) /1000;
    Score[3] = (Point % 1000) /100;
    Score[4] = (Point % 100) /10;
    Score[5] = Point % 10;
    for (k = 0; k < 6; k++) {
        B[0][k+9].NUMBER(Score[k], 15);
        B[0][k+9].PRINT(0, k+9);
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

void stage::BOMB() {
    if (BombFrame == 11) {
        EXPLOSION();
    } else if (BombFrame == 12) {
        FIREREMOVE();
        BombInBoard = false;
    } else if (BombFrame %2 == 1) {
        B[BombLine][BombColumn].BOMB1();
        B[BombLine][BombColumn].PRINT(BombLine, BombColumn);
    } else {
        B[BombLine][BombColumn].BOMB2();
        B[BombLine][BombColumn].PRINT(BombLine, BombColumn);
    }
    FrameTime += 0.2;
    BombFrame ++;
}

void stage::TIME() {
   int i;

   TotalTime--;
   if (TotalTime >= 0) {
       Time[0] = TotalTime/60; //minutos
       Time[1] = (TotalTime%60) /10; //segundos dezenas
       Time[2] = TotalTime%10 ; //segundos unidades
       for(i=0; i<3; i++) {
           B[0][i+6].NUMBER(Time[i], Color);
           B[0][i+6].PRINT(0,i+6);
       }
       StartTime = time(NULL);
   }
}





