typedef struct bomb {
	//clock de início de cada bomba
	clock_t start[9];
	//total de bombas disponíveis
	int total;
	//bombas no tabuleiro
	int inboard;
	//coordenadas de cada bomba
	int line[9], column[9];
	//frame que será executado para cada bomba
	int framenumber[9];
	//potência do fogo
	int fire;
	//slot usaodo;
	bool used[9];
};

//==============================================

typedef struct stage {
	//bomba
	bomb Bomb;

	//tabuleiro 15x15
	block B[15][15];

	//idioma do jogo
	char Language;

	//para efetuar a leitura com getch();
	char KeyColor;
	short int BomberballColor;

	//cor da fase, pallete swapping
	short int Color;

	//para guardar as probabilidades de aparecer de cada item
	int Random[100];

	//tempos
	//clock do início do jogo
	clock_t StartTime;
	int TotalTime;
	//tempo para ser exibido
	int Time[3];

	//endereço do char
	int BomberballLine, BomberballColumn;

	//numero do map
	int Stage;
	//para level up
	int ActualStage;

	//hyper efeitos
	bool InvencibleMode;
	bool WallCrossMode;
	bool SuperBombMode;
	bool SuperFireMode;

	//número de vidas/continue do bomberball
	int Life;

	//pontuações
	int Point;
	int Score[6];

	//cheatzors: passwords
	char Pass[14];

	// tecla pressionada
	char Key;
	//bloco Memoria para movimentação
	block Memory;

	void BEGIN();
	void BOMB(int i);
	void CONTROL();
	void DIE(int i, int j);
	void FIREREMOVE(int i);
	void GAME();
	void ITEM(int i, int j);
	void MOVE();
	void PASSWORD();
	void PRINT();
	void RANDOMITEM(int i, int j);
	void SCORE(int i, int j);
	void STAGE();
	void TIME();

	//construindo...
	void EXPLOSION(int i);
	void OPENING();
	void OPENING2();
	void STAGEUP();
	void WIN();
};

void stage::BEGIN() {
	int i , j;

	//inicializando a seed para o rand
	srand(time(NULL));

	//50% de chance de não ter item
	for (i = 0; i < 50; i++) {
		Random[i] = 0;
	}

	//20% de chance de ter bomb item
	for (i = 50; i < 70; i++) {
		Random[i] = 9;
	}

	//15% de chance de ter fire item
	for (i = 70; i < 85; i++) {
		Random[i] = 8;
	}

	//5% de chance de ter wall cross item
	for (i = 85; i < 90; i++) {
		Random[i] = 11;
	}

	//5% de chance de ter super bomb item
	for (i = 90; i < 95; i++) {
		Random[i] = 13;
	}

	//3% de chance de ter super fire item
	for (i = 95; i < 98; i++) {
		Random[i] = 14;
	}

	//1% de chance de ter life item
	Random[98] = 10 ;
	//1% de chance de ter invencible item
	Random[99] = 15 ;

	//inicia o stage 1
	Stage = ActualStage = 1;

	//configurações iniciais
	//3 vidas, bomba e poder de fogo em 1
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

	//ícone de vidas
	B[0][0].LIFEIT();
	B[0][1].DOT('x', 15, 0, 21);

	//ícone de fogo
	B[0][2].FIREIT();
	B[0][3].DOT('x', 15, 0, 21);

	//ícone de bomba
	B[0][4].BOMBIT();
	B[0][5].DOT('x', 15, 0, 21);

	//cheatzor
	B[14][0].LETTER('!',15);
}

//imprime estados da bomba
void stage::BOMB(int i) {
	if (Bomb.framenumber[i] == 11) {
		EXPLOSION(i);
		//som para explosão
		Beep(100,50);
	} else if (Bomb.framenumber[i] == 12) {
		FIREREMOVE(i);
		Bomb.inboard--;
		Bomb.used[i] = false;
	} else if (Bomb.framenumber[i] % 2 == 1) {
		B[Bomb.line[i]][Bomb.column[i]].NBOMB1();
		B[Bomb.line[i]][Bomb.column[i]].PRINT(Bomb.line[i], Bomb.column[i]);
	} else {
		B[Bomb.line[i]][Bomb.column[i]].NBOMB2();
		B[Bomb.line[i]][Bomb.column[i]].PRINT(Bomb.line[i], Bomb.column[i]);
	}
	Bomb.start[i] = clock();
	Bomb.framenumber[i]++;
}

//controles
void stage::CONTROL() {
	gotoxy(BomberballColumn*5+3, BomberballLine*3+3);
	Key = getch();

	//se o cara apertar enter, abra o console de cheat
	if (Key == '\r') {
		PASSWORD();

	//caso apertar espaço e se não tiver morto, solte a bomba
	} else if ( Key == ' ' && B[BomberballLine][BomberballColumn].e[4] == false  && Bomb.inboard < Bomb.total) {
		int i;

		for (i = 0;i < 9; i++) {
		    if (Bomb.used[i] == false) {//se o slot não tiver sido usado
                Bomb.line[i] = BomberballLine;
                Bomb.column[i] = BomberballColumn;
                Bomb.framenumber[i] = 1;
                Bomb.start[i] = clock();
                Bomb.inboard++;
                Bomb.used[i] = true;
                BOMB(i);
                //som para soltar bomba
                Beep(700,50);
                break;
		    }
		}

	//caso apertar botões de movimento, mexa-se
	} else if (Key == 72 || Key == 77 || Key == 80 || Key == 75) {
		MOVE();
	}
}

//morte do bomberman
//aproveita e já imprime o numero de vidas restantes
void stage::DIE(int i, int j) {
	B[i][j].BOMBERDIE();
	Beep(200,50);//som para morte
	if (Life > 0) {
		Life--;
		B[0][1].NUMBER(Life, 15);
		B[0][1].PRINT(0, 1);
	}
}

void stage::EXPLOSION(int i) {
	int f;
	bool down, up, left, right;

	down = up = right = left = false;
	B[Bomb.line[i]][Bomb.column[i]].FIRECENTER();
	B[Bomb.line[i]][Bomb.column[i]].PRINT(Bomb.line[i], Bomb.column[i]);

	// aumenta a extensão da bomba
	for (f = 1; f <= Bomb.fire; f++) {

		//cima
		if (B[Bomb.line[i]-f][Bomb.column[i]].e[1] == true) {
			up = true;
		// não coloque sobre portal ou fogo
		} else if (B[Bomb.line[i]-f][Bomb.column[i]].e[6] == false && B[Bomb.line[i]-f][Bomb.column[i]].e[7] == false) {
			// não imprime nas bordas e não atravessa blocos
			if (up == false) {
				if (B[Bomb.line[i]-f][Bomb.column[i]].e[2] == true || B[Bomb.line[i]-f][Bomb.column[i]].e[3] == true || B[Bomb.line[i]-f][Bomb.column[i]].e[5] == true) { // blocos quebráveis, itens e monsters
					B[Bomb.line[i]-f][Bomb.column[i]].BLOCK(NR, 12, 0);
					B[Bomb.line[i]-f][Bomb.column[i]].e[7] = true;
					SCORE(Bomb.line[i]-f, Bomb.column[i]);
					//função randômica para itens
					if (B[Bomb.line[i]-f][Bomb.column[i]].e[2] == true) {
						RANDOMITEM(Bomb.line[i]-f, Bomb.column[i]);
					}

					//se a superbombmode não estiver ativada
					if (SuperBombMode == false) {
						up = true;
					}

				//outra bomba chama a função recursivamente, se é que vai ter.
				} else if (B[Bomb.line[i]-f][Bomb.column[i]].e[4] == true) {
				    int j;
				    for (j = 0; j < 9; j++) {
				        if (Bomb.line[j] == Bomb.line[i]-f && Bomb.column[j] == Bomb.column[i]) {
                            Bomb.start[j] = Bomb.start[i];
                            Bomb.framenumber[j] = Bomb.framenumber[i];
                            BOMB(j);
				        }
				    }
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[i]-f][Bomb.column[i]].FIREUP();
					} else {
						B[Bomb.line[i]-f][Bomb.column[i]].FIREVLINE();
					}
				}
				B[Bomb.line[i]-f][Bomb.column[i]].PRINT(Bomb.line[i]-f, Bomb.column[i]);
			}
		}

		//baixo
		//muito provavelmente o bug está aqui...
		if (B[Bomb.line[i]+f][Bomb.column[i]].e[1] == true) {
			down = true;
		} else if (B[Bomb.line[i]+f][Bomb.column[i]].e[6] == false && B[Bomb.line[i]+f][Bomb.column[i]].e[7] == false) {
			if (down == false) {
				if (B[Bomb.line[i]+f][Bomb.column[i]].e[2] == true || B[Bomb.line[i]+f][Bomb.column[i]].e[3] == true || B[Bomb.line[i]+f][Bomb.column[i]].e[5] == true) {
					B[Bomb.line[i]+f][Bomb.column[i]].BLOCK(NR, 12, 0);
					B[Bomb.line[i]+f][Bomb.column[i]].e[7] = true;
					SCORE(Bomb.line[i]+f, Bomb.column[i]);

					if (B[Bomb.line[i]+f][Bomb.column[i]].e[2] == true) {
						RANDOMITEM(Bomb.line[i]+f, Bomb.column[i]);
					}

					if (SuperBombMode == false) {
						down = true;
					}
				} else if (B[Bomb.line[i]+f][Bomb.column[i]].e[4] == true) {
					int j;
				    for (j = 0; j < 9; j++) {
				        if (Bomb.line[j] == Bomb.line[i]+f && Bomb.column[j] == Bomb.column[i]) {
                            Bomb.start[j] = Bomb.start[i];
                            Bomb.framenumber[j] = Bomb.framenumber[i];
                            BOMB(j);
				        }
				    }
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[i]+f][Bomb.column[i]].FIREDOWN();
					} else {
						B[Bomb.line[i]+f][Bomb.column[i]].FIREVLINE();
					}
				}
				B[Bomb.line[i]+f][Bomb.column[i]].PRINT(Bomb.line[i]+f, Bomb.column[i]);
			}
		}

		// esq.
		if (B[Bomb.line[i]][Bomb.column[i]-f].e[1] == true) {
			left = true;
		} else if (B[Bomb.line[i]][Bomb.column[i]-f].e[6] == false && B[Bomb.line[i]][Bomb.column[i]-f].e[7] == false) {
			if (left == false) {
				if (B[Bomb.line[i]][Bomb.column[i]-f].e[2] == true || B[Bomb.line[i]][Bomb.column[i]-f].e[3] == true || B[Bomb.line[i]][Bomb.column[i]-f].e[5] == true) {
					B[Bomb.line[i]][Bomb.column[i]-f].BLOCK(NR, 12, 0);
					B[Bomb.line[i]][Bomb.column[i]-f].e[7] = true;
					SCORE(Bomb.line[i], Bomb.column[i]-f);

					if (B[Bomb.line[i]][Bomb.column[i]-f].e[2] == true) {//função randômica para itens
						RANDOMITEM(Bomb.line[i], Bomb.column[i]-f);
					}

					if (SuperBombMode == false) {
						left = true;
					}
				} else if (B[Bomb.line[i]][Bomb.column[i]-f].e[4] == true) {
					int j;
				    for (j = 0; j < 9; j++) {
				        if (Bomb.line[j] == Bomb.line[i] && Bomb.column[j] == Bomb.column[i]-f) {
                            Bomb.start[j] = Bomb.start[i];
                            Bomb.framenumber[j] = Bomb.framenumber[i];
                            BOMB(j);
				        }
				    }
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[i]][Bomb.column[i]-f].FIRELEFT();
					} else {
						B[Bomb.line[i]][Bomb.column[i]-f].FIREHLINE();
					}
				}
				B[Bomb.line[i]][Bomb.column[i]-f].PRINT(Bomb.line[i], Bomb.column[i]-f);
			}
		}

		//direita
		if (B[Bomb.line[i]][Bomb.column[i]+f].e[1] == true) {
			right = true;
		} else if (B[Bomb.line[i]][Bomb.column[i]+f].e[6] == false && B[Bomb.line[i]][Bomb.column[i]+f].e[7] == false) {
			if (right == false) {
				if (B[Bomb.line[i]][Bomb.column[i]+f].e[2] == true || B[Bomb.line[i]][Bomb.column[i]+f].e[3] == true || B[Bomb.line[i]][Bomb.column[i]+f].e[5] == true) {
					B[Bomb.line[i]][Bomb.column[i]+f].BLOCK(NR, 12, 0);
					B[Bomb.line[i]][Bomb.column[i]+f].e[7] = true;
					SCORE(Bomb.line[i], Bomb.column[i]+f);

					if (B[Bomb.line[i]][Bomb.column[i]+f].e[2] == true) {//função randômica para itens
						RANDOMITEM(Bomb.line[i], Bomb.column[i]+f);
					}
					if (SuperBombMode == false) {
						right = true;
					}
				} else if (B[Bomb.line[i]][Bomb.column[i]+f].e[4] == true) {
					int j;
				    for (j = 0; j < 9; j++) {
				        if (Bomb.line[j] == Bomb.line[i] && Bomb.column[j] == Bomb.column[i]+f) {
                            Bomb.start[j] = Bomb.start[i];
                            Bomb.framenumber[j] = Bomb.framenumber[i];
                            BOMB(j);
				        }
				    }
				} else {
					if (f == Bomb.fire) {
						B[Bomb.line[i]][Bomb.column[i]+f].FIRERIGHT();
					} else {
						B[Bomb.line[i]][Bomb.column[i]+f].FIREHLINE();
					}
				}
				B[Bomb.line[i]][Bomb.column[i]+f].PRINT(Bomb.line[i], Bomb.column[i]+f);
			}
		}
	}
}

//desenhos do fogo, reto
void stage::FIREREMOVE(int i) {
	int f;

	for (f = 1;f <= Bomb.fire; f++) {
		//para cima
		if (B[Bomb.line[i]-f][Bomb.column[i]].e[7] == true && Bomb.line[i]-f >= 2) {
			B[Bomb.line[i]-f][Bomb.column[i]].ZERO();
			B[Bomb.line[i]-f][Bomb.column[i]].PRINT(Bomb.line[i]-f, Bomb.column[i]);
		}
		//baixo
		if (B[Bomb.line[i]+f][Bomb.column[i]].e[7] == true && Bomb.line[i]+f <= 12) {
			B[Bomb.line[i]+f][Bomb.column[i]].ZERO();
			B[Bomb.line[i]+f][Bomb.column[i]].PRINT(Bomb.line[i]+f, Bomb.column[i]);
		}
		//esq.
		if (B[Bomb.line[i]][Bomb.column[i]-f].e[7] == true && Bomb.column[i]-f >= 2) {
			B[Bomb.line[i]][Bomb.column[i]-f].ZERO();
			B[Bomb.line[i]][Bomb.column[i]-f].PRINT(Bomb.line[i], Bomb.column[i]-f);
		}
		//direita
		if (B[Bomb.line[i]][Bomb.column[i]+f].e[7] == true && Bomb.column[i]+f <= 12) {
			B[Bomb.line[i]][Bomb.column[i]+f].ZERO();
			B[Bomb.line[i]][Bomb.column[i]+f].PRINT(Bomb.line[i], Bomb.column[i]+f);
		}
	}
	//centro de explosão
	B[Bomb.line[i]][Bomb.column[i]].ZERO();
	B[Bomb.line[i]][Bomb.column[i]].PRINT(Bomb.line[i], Bomb.column[i]);
}

void stage::GAME() {
	int i, j;

	//posição inicial (2, 2)
	BomberballLine = BomberballColumn = 2;

	//5 minutos
	Time[0] = 5;
	Time[1] = Time[2] = 0;

	//zera memória
	Memory.ZERO();

	//sem bombas no tabuleiro
	Bomb.inboard = 0;

	for (i = 0;i < 9; i++) {
	    Bomb.used[i] = false;
	}

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
				B[i][j].BLOCK(NR, Color, 0);
				//e[1] = bloco inquebravel
				B[i][j].e[1] = true;
			}
		}
	}

	//bomberball
	B[2][2].HERO(BomberballColor);

	//imprime quantidade de vidas
	B[0][1].NUMBER(Life, 15);
	//imprime poder de fogo
	B[0][3].NUMBER(Bomb.fire, 15);
	//imprime quantidade de bombas
	B[0][5].NUMBER(Bomb.total, 15);

	//imprime tempo INICIAL
	B[0][6].NUMBER(Time[0], Color);
	B[0][7].NUMBER(Time[1], Color);
	B[0][7].DOT(':', Color, 0, 21);
	B[0][8].NUMBER(Time[2], Color);

	//imprime a pontuação
	B[0][9].NUMBER(Score[0], 15);
	B[0][10].NUMBER(Score[1], 15);
	B[0][11].NUMBER(Score[2], 15);
	B[0][12].NUMBER(Score[3], 15);
	B[0][13].NUMBER(Score[4], 15);
	B[0][14].NUMBER(Score[5], 15);

	//Fase
	//L10N: Eng
	if (Language == '1') {
		B[2][0].LETTER('S', Color);
		B[3][0].LETTER('T', Color);
		B[4][0].LETTER('A', Color);
		B[5][0].LETTER('G', Color);
		B[6][0].LETTER('E', Color);
		B[8][0].NUMBER(Stage, Color);
	//Português
	} else {
		B[2][0].LETTER('F', Color);
		B[3][0].LETTER('A', Color);
		B[4][0].LETTER('S', Color);
		B[5][0].LETTER('E', Color);
		B[7][0].NUMBER(Stage, Color);
	}

	//tabuleiro, para teste
	B[2][9].MONSTER();
	B[12][12].GATE();

	PRINT();

	gotoxy(1,50);
	textcolor(15);

	//English
	if (Language == '1') {
		printf("\nPress:\nDirectional Keys to move\nSPACE to use bomb\nENTER to pause");
	//Português
	} else {
		printf("\nPressione:\nTeclas Direcionais para mover\nSPACE para soltar bomba\nENTER para pausar");
	}
	//fim tabuleiro testes

	//matriz de debug
	printf("\n");
	for (i = 0;i < 15; i++){
		for (j = 0;j < 15; j++) {
			printf("%d ", B[i][j].e[1]); {
		}
	}
		printf("\n");
	}

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
				for (i = 0;i < 9; i++) {
                    if (Bomb.used[i] == true) {
                        if (clock() - Bomb.start[i] >= 0.2 * CLOCKS_PER_SEC) {
                            BOMB(i);
                        }
                    }
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

//efeitos dos items
void stage::ITEM(int i, int j) {
	//som para item
	Beep(2500,50);
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
	} else if (B[i][j].e[11] == true) {
		WallCrossMode = true;
		B[2][14].WALLIT();
		B[2][14].PRINT(2, 14);
	} else if (B[i][j].e[10] == true) {
		if (Life<9) {
			Life++;
			B[0][1].NUMBER(Life, 15);
			B[0][1].PRINT(0,1);
		}
	} else if (B[i][j].e[13] == true) {
		SuperBombMode = true;
		B[4][14].SBOMBIT();
		B[4][14].PRINT(4, 14);
	} else if(B[i][j].e[14] == true) {
		SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT();
		B[5][14].PRINT(5,14);
	} else if (B[i][j].e[15] == true) {
		InvencibleMode = true;
		B[3][14].INVENCIBLEIT();
		B[3][14].PRINT(3, 14);
	}
}

//movimentação
//KEY_UP	= 72
//KEY_RIGHT	= 77
//KEY_DOWN	= 80
//KEY_LEFT	= 75
void stage::MOVE() {
	int down, right;
	down = right = 0;

	if (Key == 72 ) {
		down = -1;
	} else if (Key == 80) {
		down = 1;
	} else if (Key == 75) {
		right = -1;
	} else if (Key == 77) {
		right = 1;
	}

	if (WallCrossMode == true || (WallCrossMode == false && B[BomberballLine+down][BomberballColumn+right].e[17] == false ) || B[BomberballLine+down][BomberballColumn+right].e[6] == true) {
		if((Key == 72 && BomberballLine > 2 ) || (Key == 80 && BomberballLine < 12) || (Key == 75 && BomberballColumn > 2) || (Key == 77 && BomberballColumn < 12)) {
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
					B[BomberballLine+down][BomberballColumn+right].HERO(BomberballColor);
				}

				B[BomberballLine+down][BomberballColumn+right].PRINT(BomberballLine+down, BomberballColumn+right);

				if (Key == 72 || Key == 80) {
					BomberballLine += down;
				} else {
					BomberballColumn += right;
				}
			}
		}
	}
}

void stage::OPENING() {
	int i, j, x;
	block A[10][15];

	for(i = 0; i < 10; i++) {
		for (j = 0; j < 15; j++) {
		A[i][j].ZERO();
		A[i][j].BLOCK(0, 0, 15);
	}
	}

	//logo da uel
	A[1][2].DOT(NR, 0, 0, 23);
	A[1][2].DOT(NR, 0, 0, 31);
	A[1][2].DOT(NR, 0, 0, 33);
	A[1][2].VLINE(NR, 0, 0, 5);
	A[1][3].CIRCLE(10, 15);
	A[1][4].DOT(NR, 0, 0, 23);
	A[1][4].DOT(NR, 0, 0, 33);
	A[1][4].DOT(NR, 0, 0, 35);
	A[1][4].VLINE(NR, 0, 0, 1);
	A[2][2].VLINE(NR, 0, 0, 1);
	A[2][2].VLINE(NR, 0, 0, 3);
	A[2][2].VLINE(NR, 0, 0, 5);
	A[2][3].VLINE(NR, 10, 0, 3);
	A[2][4].VLINE(NR, 0, 0, 1);
	A[2][4].VLINE(NR, 0, 0, 3);
	A[2][4].VLINE(NR, 0, 0, 5);
	A[3][2].BLOCK(DR, 0, 15);
	A[3][2].HLINE(NR, 0, 0, 1);
	A[3][2].DOT(NR, 15, 0, 21);
	A[3][2].DOT(NR, 15, 0, 31);
	A[3][2].DOT(NR, 15, 0, 32);
	A[3][3].BLOCK(DR, 0, 15);
	A[3][3].HLINE(NR, 0, 0, 1);
	A[3][3].VLINE(NR, 10, 0, 3);
	A[3][4].BLOCK(DR, 0, 15);
	A[3][4].HLINE(NR, 0, 0, 1);
	A[3][4].DOT(NR, 15, 0, 25);
	A[3][4].DOT(NR, 15, 0, 34);
	A[3][4].DOT(NR, 15, 0, 35);

	//Imprime
	for (i = 0; i < 10; i++) {
		for (x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}

	gotoxy(40, 5);
	printf("Ernesto Yuiti Saito");

	gotoxy(40, 8);
	printf("Hayato Fujii");

	gotoxy(40, 11);
	printf("Marcos Okamura Rodrigues\n");

	gotoxy(25, 20);
	printf("Ciencia da Computacao UEL - 2009");

	gotoxy(1, 35);
}

void stage::OPENING2() {
	int i, j, x;
	block A[10][15];

	for(i = 0; i < 10; i++) {
		for (j = 0; j < 15; j++) {
			A[i][j].ZERO();
		}
	}

	A[1][2].LETTER('B', 14);
	A[1][3].LETTER('O', 14);
	A[1][4].LETTER('M', 14);
	A[1][5].LETTER('B', 14);
	A[1][6].LETTER('E', 14);
	A[1][7].LETTER('R', 14);
	A[1][8].LETTER('B', 14);
	A[1][9].LETTER('A', 14);
	A[1][10].LETTER('L', 14);
	A[1][11].LETTER('L', 14);

	A[3][7].DOT(DR, 13, 0, 33);//Bomberball
	A[4][7].BOMBERBALL(15, 0);
	A[5][6].DOT(DR, 15, 0, 15);
	A[5][6].DOT(UR, 13, 0, 24);
	A[5][7].VLINE(NR, 1, 0, 2);
	A[5][7].VLINE(NR, 1, 0, 3);
	A[5][7].VLINE(NR, 1, 0, 4);
	A[5][7].DOT(UR, 15, 0, 11);
	A[5][7].DOT(UR, 15, 0, 15);
	A[5][7].DOT(DR, 14, 1, 23);
	A[5][8].DOT(DR, 15, 0, 11);
	A[5][8].DOT(UR, 13, 0, 22);
	A[6][7].DOT(NR, 15, 0, 12);
	A[6][7].DOT(NR, 15, 0, 14);
	A[6][7].DOT(DR, 13, 15, 22);
	A[6][7].DOT(DR, 13, 15, 24);

	for (i = 0; i < 10; i++) {//Imprime
		for (x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}

	gotoxy(1, 35);
}

//entrada de cheats
void stage::PASSWORD() {
	int j;
	char ch;

	B[14][0].LETTER('!', 12);
	B[14][0].PRINT(14, 0);

	j = 0;
	ch = getch();
	while (ch != '\r' && j < 14) {
		Pass[j] = ch;
		B[14][j+1].LETTER(Pass[j], 15);
		B[14][j+1].PRINT(14, j+1);
		ch = getch();
		j++;
	}

	if (j < 14) {
		Pass[j] = '\0';
	}

	if (strcmp(Pass, "invencible") == 0) {
		InvencibleMode = true;
		B[3][14].INVENCIBLEIT();
		B[3][14].PRINT(3, 14);
	} else if (strcmp(Pass, "superbomb") == 0) {
		SuperBombMode = true;
		B[4][14].SBOMBIT();
		B[4][14].PRINT(4, 14);
	} else if (strcmp(Pass, "wallcross") == 0) {
		WallCrossMode = true;
		B[2][14].WALLIT();
		B[2][14].PRINT(2, 14);
	} else if (strcmp(Pass, "superfire") == 0) {
		SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT();
		B[5][14].PRINT(5,14);
	} else if (strcmp(Pass, "stageup") == 0) {
	    ActualStage++;
	}
	B[14][0].LETTER('!', 14);
	B[14][0].PRINT(14, 0);
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

void stage::RANDOMITEM(int i, int j) {
	int k;

	//atribui um valor randômico para k
	k = rand()%100;

	if (Random[k] != 0) {
		switch (Random[k]) {
			case 8: B[i][j].FIREIT(); break;
			case 9: B[i][j].BOMBIT(); break;
            case 10: B[i][j].LIFEIT(); break;
            case 11: B[i][j].WALLIT(); break;
			case 13: B[i][j].SBOMBIT(); break;
			case 14: B[i][j].SFIREIT(); break;
			case 15: B[i][j].INVENCIBLEIT();
		}
		B[i][j].PRINT(i, j);
		//retira o efeito de fogo
		B[i][j].e[7] = false;
		//retira o efeito para poder pegar o item
		B[i][j].e[17] = false;
	}
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

	Score[0] = Point / 100000;
	Score[1] = (Point % 100000)/10000;
	Score[2] = (Point % 10000)/1000;
	Score[3] = (Point % 1000)/100;
	Score[4] = (Point % 100)/10;
	Score[5] = Point % 10;

	for (k = 0; k < 6; k++) {
		B[0][k+9].NUMBER(Score[k], 15);
		B[0][k+9].PRINT(0, k+9);
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

//zera o tabuleiro central
	for (i = 2; i < 13; i++) {
		for (j = 2; j < 13; j++) {
			B[i][j].ZERO();
		}
	}

	//tabuleiros
	if (Stage == 1) {
		for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i%2 == 0 && j%2 == 0) {
					B[i][j].BLOCK(SQ, Color, 0);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
					B[i][j].e[17] = true;
				}
			}
		}
	} else if (Stage == 2) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (i%2 == 1) {
					B[i][j].BLOCK(SQ, Color, 0);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
					B[i][j].e[17] = true;
				}
			}
		}
	} else if (Stage == 3) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (j%2 == 1) {
					B[i][j].BLOCK(SQ, Color, 0);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
					B[i][j].e[17] = true;
				}
			}
		}
	} else if (Stage == 4) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if ((i%2 == 1 && i != 7) || (j%2 == 1 && j != 7)) {
					B[i][j].BLOCK(SQ, Color, 0);
					//e[2] = bloco quebravel
					B[i][j].e[2] = true;
					B[i][j].e[17] = true;
				}
			}
		}
	}
}

void stage::STAGEUP() {
    block A[1][15];
    int j, x;

    system("cls");
    for (j = 0; j < 15; j++) {
        A[0][j].ZERO();
    }
    if (Language == '1') {
        A[0][4].LETTER('S', 15);
        A[0][5].LETTER('T', 15);
        A[0][6].LETTER('A', 15);
        A[0][7].LETTER('G', 15);
        A[0][8].LETTER('E', 15);
        A[0][10].NUMBER(Stage, 15);
    }
    else {
        A[0][4].LETTER('F',15);
        A[0][5].LETTER('A', 15);
        A[0][6].LETTER('S', 15);
        A[0][7].LETTER('E', 15);
        A[0][9].NUMBER(Stage, 15);
    }

    //Imprime
    gotoxy(1, 20);
    for (x = 1; x < 4; x++) {
        textcolor(0);
        printf("  ");
        for (j = 0; j < 15; j++) {
            A[0][j].PRINTLINE(x);
        }
    printf("\n");
	}
	//Aguarde 2 segundo para iniciar a fase
    wait(2000);
    system("cls");
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
		StartTime = clock();
	}
}

void stage::WIN() {
    block A[1][15];
    int j, x;

    system("cls");
    for (j = 0; j < 15; j++) {
        A[0][j].ZERO();
    }
    if (Language == '1') {
        A[0][4].LETTER('Y', 15);
        A[0][5].LETTER('O', 15);
        A[0][6].LETTER('U', 15);
        A[0][8].LETTER('W', 15);
        A[0][9].LETTER('O', 15);
        A[0][10].LETTER('N', 15);
        A[0][11].LETTER('!', 15);
    }
    else {
        A[0][2].LETTER('V',15);
        A[0][3].LETTER('O', 15);
        A[0][4].LETTER('C', 15);
        A[0][5].LETTER('E', 15);
        A[0][7].LETTER('V',15);
        A[0][8].LETTER('E', 15);
        A[0][9].LETTER('N', 15);
        A[0][10].LETTER('C', 15);
        A[0][11].LETTER('E',15);
        A[0][12].LETTER('U', 15);
        A[0][13].LETTER('!', 15);
    }

    //Imprime
    gotoxy(1, 20);
    for (x = 1; x < 4; x++) {
        textcolor(0);
        printf("  ");
        for (j = 0; j < 15; j++) {
            A[0][j].PRINTLINE(x);
        }
    printf("\n");
	}
	wait(2000);
}
