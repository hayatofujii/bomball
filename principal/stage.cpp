typedef struct stage {
	//bomba
	bomb Bomb;

	hero Bomberball;

	monster Monster;

	//tabuleiro 15x15
	block B[15][15];

	//idioma do jogo
	char Language;

	//cor da fase, pallete swapping
	short int Color;

	//para guardar as probabilidades de aparecer de cada item
	char Randomitem[100];
	//para guardar as posições das casas vazias
	int Randommonster[100];

	//tempos
	//clock do início do jogo e de cada atualização de monstros
	clock_t StartTime, MonsterTime, BossTime;
	int TotalTime;
	//tempo para ser exibido
	int Time[3];

	// indica se o portal foi impresso
	bool Gate;
	//numero do map
	int Stage;
	//level dos monstros
	int Level;
	// velocidade do chefão
	float BossSpeed;
	//numero de blocos vazios
	int Nullspaces;
	//para level up
	int ActualStage;
	int ActualLife;
	// para aumentar vida
	int LifeUp;

	//modos
	bool InvencibleMode, WallCrossMode, SuperBombMode, SuperFireMode, BombKickMode, BombPunchMode, TimeBombMode;

	//clock do início do modo invencível
	clock_t InvencibleStart;

	//pontuações
	int Point;
	int Score[6];

	//cheatzors: passwords
	char Pass[14];

	// tecla pressionada
	char Key;
	//último movimento
	char LastMove;
	//bloco Memoria para movimentação
	block Memory, Memory2;

    //som
    FSOUND_SAMPLE *sound;

	//***Funções****

	//bomba
	void BOMB(int i);
	void EXPLOSION(int i);
	void FIREREMOVE(int i);

	//jogo
	void BEGIN();
	void GAME();
	void STAGE();

	//infra-estrutura
	void BOMBKICK(int i);
	void BOMBPUNCH(int i);
	void BOSS();
	void DIE();
	void ITEM(int i, int j);
	void PASSWORD();
	void PRINT();
	void SCORE(int i, int j);
	void TIME();

	//movimentação
	void BOSSMOVE(int i);
	void CONTROL();
	bool GO(int i, int co, int n);
	void HUNTERMOVE(int i);
	void MONSTERMOVE(int i, char move);
	void MOVE();
    void RANDOMMOVE(int i);

	//random
	void RANDOMITEM(int i, int j);
	void RANDOMMONSTER(int level);
	void RANDOMGATE();

	//texto
	void CONTINUE();
	void END(bool win);
	void OPENING();
	void OPENING2();
	void STAGEOP();
};

void stage::BEGIN() {
	int i , j;

	//inicializando a seed para o rand
	srand(time(NULL));

	//50% de chance de não ter item
	for (i = 0; i < 50; i++) {
		Randomitem[i] = '0';
	}

	//15% de chance de ter bomb item
	for (i = 50; i < 65; i++) {
		Randomitem[i] = 'b';
	}

	//15% de chance de ter fire item
	for (i = 65; i < 80; i++) {
		Randomitem[i] = 'f';
	}

	//3% de chance de ter punch item
	for (i = 80; i < 83; i++) {
		Randomitem[i] = 'p';
	}

	//3% de chance de ter kick item
	for (i = 83; i < 86; i++) {
		Randomitem[i] = 'k';
	}

	//3% de chance de ter wall cross item
	for (i = 86; i < 89; i++) {
		Randomitem[i] = 'w';
	}

	//3% de chance de ter time bomb item
	for (i = 89; i < 92; i++) {
		Randomitem[i] = 't';
	}

	//3% de chance de ter super bomb item
	for (i = 92; i < 95; i++) {
		Randomitem[i] = 'B';
	}

	//3% de chance de ter super fire item
	for (i = 95; i < 98; i++) {
		Randomitem[i] = 'F';
	}

	//1% de chance de ter life item
	Randomitem[98] = 'l' ;
	//1% de chance de ter invencible item
	Randomitem[99] = 'i' ;

	//inicia o stage 1
	Stage = ActualStage = 1;

	//configurações iniciais
	//3 vidas, bomba e poder de fogo em 1
	Bomberball.life = ActualLife = 3;
	Bomb.total = Bomb.fire = 1;

	//pontuação para ganhar vida
	LifeUp = 10000;

	//zera pontuação
	for (i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	Point = 0;

	//zera modos
	WallCrossMode = SuperBombMode = SuperFireMode = InvencibleMode = BombKickMode = BombPunchMode = TimeBombMode = false;

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
		//som para explosão
		sound = FSOUND_Sample_Load (1, "sons\\Explosao 02.wma", 0, 0, 0);
        FSOUND_PlaySound (1, sound);
        FSOUND_SetVolume(1, 255);
        EXPLOSION(i);
    } else if (Bomb.framenumber[i] == 12) {
		FIREREMOVE(i);
		Bomb.inboard--;
		Bomb.used[i] = false;
	} else if (Bomb.framenumber[i] % 2 == 1) {
		if (SuperBombMode == false) {
		    if (TimeBombMode == false) {
                B[Bomb.co[i].y][Bomb.co[i].x].NBOMB1();
		    } else {
		        B[Bomb.co[i].y][Bomb.co[i].x].TBOMB1();
		        Bomb.framenumber[i] = 1;
		    }
		}
		else {
		    if (TimeBombMode == false) {
                B[Bomb.co[i].y][Bomb.co[i].x].SBOMB1();
		    } else {
		        B[Bomb.co[i].y][Bomb.co[i].x].STBOMB1();
		        Bomb.framenumber[i] = 1;
		    }
		}
		B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	} else {
	    if (SuperBombMode == false) {
		    if (TimeBombMode == false) {
                B[Bomb.co[i].y][Bomb.co[i].x].NBOMB2();
		    } else {
		        B[Bomb.co[i].y][Bomb.co[i].x].TBOMB2();
		        Bomb.framenumber[i] = 2;
		    }
		}
		else {
		    if (TimeBombMode == false) {
                B[Bomb.co[i].y][Bomb.co[i].x].SBOMB2();
		    } else {
		        B[Bomb.co[i].y][Bomb.co[i].x].STBOMB2();
		        Bomb.framenumber[i] = 2;
		    }
		}
		B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	}
	Bomb.start[i] = clock();
	Bomb.framenumber[i]++;
}

//controles
void stage::CONTROL() {
	gotoxy(Bomberball.co.x*5+3, Bomberball.co.y*3+3);
	Key = getch();

	//se o cara apertar enter, abra o console de cheat
	if (Key == KEY_START) {
		PASSWORD();

	//se apertar a bomba relógio e estiver ativado o modo timebomb
	} else if (Key == KEY_TBOMB && TimeBombMode == true) {
        int i;
        if (Bomb.inboard > 0) {
            for (i = 0; i < 9; i++) {
                if (Bomb.used[i] == true) {
                    Bomb.framenumber[i] = 11;
                    BOMB(i);
                }
            }
        }

	//se apertar soco e tiver ativado o modo bombpunch
	} else if (Key == KEY_PUNCH && BombPunchMode == true) {
		int i;
		switch (LastMove) {
			case KEY_RIGHT: {
				if (B[Bomberball.co.y][Bomberball.co.x+1].e[4] == true) {
					i = B[Bomberball.co.y][Bomberball.co.x+1].bslot;
					BOMBPUNCH(i);
				 }
			}break;
			case KEY_DOWN: {
				if (B[Bomberball.co.y+1][Bomberball.co.x].e[4] == true) {
					i = B[Bomberball.co.y+1][Bomberball.co.x].bslot;
					BOMBPUNCH(i);
				}
			}break;
			case KEY_LEFT: {
				if (B[Bomberball.co.y][Bomberball.co.x-1].e[4] == true) {
					i = B[Bomberball.co.y][Bomberball.co.x-1].bslot;
					BOMBPUNCH(i);
				}
			}break;
			case KEY_UP: {
				if (B[Bomberball.co.y-1][Bomberball.co.x].e[4] == true) {
					i = B[Bomberball.co.y-1][Bomberball.co.x].bslot;
					BOMBPUNCH(i);
				}
			}
		}

	//caso apertar espaço e não houver outra bomba, nem bloco SQ, solte a bomba
	} else if (Key == KEY_BOMB && Memory2.e[2] == false && B[Bomberball.co.y][Bomberball.co.x].e[4] == false  && Bomb.inboard < Bomb.total) {
		int i;

		for (i = 0; i < 9; i++) {
			if (Bomb.used[i] == false) {//se o slot não tiver sido usado
				Bomb.co[i].SET(Bomberball.co.x, Bomberball.co.y);
				Bomb.inboard++;
                Bomb.used[i] = true;
                B[Bomb.co[i].y][Bomb.co[i].x].bslot = i;
				Bomb.start[i] = clock();
                Bomb.framenumber[i] = 1;
                BOMB(i);
				Memory2 = B[Bomb.co[i].y][Bomb.co[i].x];
				//som para soltar bomba
				sound = FSOUND_Sample_Load (3, "sons\\Implantando Bomba.wav", 0, 0, 0);
				FSOUND_PlaySound (3, sound);
				FSOUND_SetVolume(3, 255);
                break;
			}
		}

	//caso apertar botões de movimento, mexa-se
	} else if (Key == KEY_UP || Key == KEY_DOWN || Key == KEY_LEFT || Key == KEY_RIGHT) {
		int i;
		LastMove = Key;
		MOVE();
	}
}

//morte do bomberman
//aproveita e já imprime o numero de vidas restantes
void stage::DIE() {

	B[Bomberball.co.y-1][Bomberball.co.x].BOMBERDIE();
	B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
	B[Bomberball.co.y][Bomberball.co.x].BODY(12, LastMove);
	B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);
	//som para morte
	Beep(200,50);
	if (ActualLife > 0 && ActualLife == Bomberball.life) {
		ActualLife--;
		B[0][1].NUMBER(ActualLife, 15);
		B[0][1].PRINT(0, 1);
	}
}

void stage::EXPLOSION(int i) {
	int f, j;
	bool down, up, left, right;

	down = up = right = left = false;
	// se o bomberball estiver em cima da bomba
	if (Bomb.co[i].EQUAL(Bomberball.co) && InvencibleMode == false) {
		DIE();
	} else if (Bomb.co[i].EQUAL(Bomberball.co.x, Bomberball.co.y-1) == false) {
		B[Bomb.co[i].y][Bomb.co[i].x].FIRECENTER();
	}
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	// aumenta a extensão da bomba
	for (f = 1; f < Bomb.fire+1; f++) {

		//cima
		if (Bomb.co[i].y-f >= 2) {
			if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[1] == true) {
				up = true;
			// não coloque sobre portal ou fogo
			} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[6] == false && B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == false) {
				// não imprime nas bordas e não atravessa blocos
				if (up == false) {
					//blocos quebráveis
					if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[2] == true) {
						if (Memory.e[2] == false) {
                            B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y-f, Bomb.co[i].x);
						RANDOMITEM(Bomb.co[i].y-f, Bomb.co[i].x);
						if (Bomb.co[i].y-f == Bomberball.co.y-1 && Bomb.co[i].x == Bomberball.co.x) {
                            if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == false) {
                                Memory = B[Bomb.co[i].y-f][Bomb.co[i].x];
                            } else {
                                Memory.ZERO();
                            }
                        }
						// se a superbombmode não estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}

					//itens
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[3] == true) {
						if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[9] == false) {
                            B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						//se a superbombmode não estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}

					//monsters
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[5] == true) {
						if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[9] == false) {
                            B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y-f, Bomb.co[i].x);
						j = B[Bomb.co[i].y-f][Bomb.co[i].x].mslot;
						Monster.life[j]--;
						if (Stage % 5 ==0 && j == 0) {
						    if (Monster.life[j] == 0) {
						        B[11][14].ZERO();
						    } else {
                                B[11][14].NUMBER(Monster.life[j], 15);
						    }
						    B[11][14].PRINT(11, 14);
						}
						if (Monster.life[j] == 0) {
                            Monster.inboard--;
						}
						//se a superbombmode não estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}
					//outra bomba chama a função recursivamente
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[4] == true) {
						if (TimeBombMode == false) {
                            int j;
                            for (j = 0; j < 9; j++) {
                                if (Bomb.co[j].y == Bomb.co[i].y-f && Bomb.co[j].x == Bomb.co[i].x) {
                                    Bomb.start[j] = Bomb.start[i];
                                    Bomb.framenumber[j] = Bomb.framenumber[i];
                                    BOMB(j);
                                }
                            }
						}
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[8] == true && InvencibleMode == false) {//se o bomberball estiver na linha da bomba
						DIE();
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[9] == false){
					    if (f == Bomb.fire) {
							B[Bomb.co[i].y-f][Bomb.co[i].x].FIREUP();
						} else {
							B[Bomb.co[i].y-f][Bomb.co[i].x].FIREVLINE();
						}
					}
					B[Bomb.co[i].y-f][Bomb.co[i].x].PRINT(Bomb.co[i].y-f, Bomb.co[i].x);

				}
			}
		}

		//baixo
		if(Bomb.co[i].y+f <= 12){
			if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[1] == true) {
				down = true;
			} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[6] == false && B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] == false) {
				if (down == false) {
					if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[2] == true ) {
						if (Memory.e[2] == false) {
                            B[Bomb.co[i].y+f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y+f, Bomb.co[i].x);
						RANDOMITEM(Bomb.co[i].y+f, Bomb.co[i].x);
						if (Bomb.co[i].y+f == Bomberball.co.y-1 && Bomb.co[i].x == Bomberball.co.x) {
                            if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] == false) {
                                Memory = B[Bomb.co[i].y+f][Bomb.co[i].x];
                            } else {
                                Memory.ZERO();
                            }
                        }

						if (SuperBombMode == false) {
							down = true;
						}
					} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[3] == true) {
						if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[9] == false) {
                            B[Bomb.co[i].y+f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] = true;

						if (SuperBombMode == false) {
							down = true;
						}

					} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[5] == true) {
						if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[9] == false) {
                            B[Bomb.co[i].y+f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y+f, Bomb.co[i].x);
						j = B[Bomb.co[i].y+f][Bomb.co[i].x].mslot;
						Monster.life[j]--;
						if (Stage % 5 ==0 && j == 0) {
						    if (Monster.life[j] == 0) {
						        B[11][14].ZERO();
						    } else {
                                B[11][14].NUMBER(Monster.life[j], 15);
						    }
						    B[11][14].PRINT(11, 14);
						}
						if (Monster.life[j] == 0) {
                            Monster.inboard--;
						}
						if (SuperBombMode == false) {
							down = true;
						}
					} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[4] == true) {
						if (TimeBombMode == false) {
                            int j;
                            for (j = 0; j < 9; j++) {
                                if (Bomb.co[j].y == Bomb.co[i].y+f && Bomb.co[j].x == Bomb.co[i].x) {
                                    Bomb.start[j] = Bomb.start[i];
                                    Bomb.framenumber[j] = Bomb.framenumber[i];
                                    BOMB(j);
                                }
                            }
						}
					} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[8] == true && InvencibleMode == false) {
						DIE();
					} else if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[9] == false) {
						if (f == Bomb.fire) {
							B[Bomb.co[i].y+f][Bomb.co[i].x].FIREDOWN();
						} else {
							B[Bomb.co[i].y+f][Bomb.co[i].x].FIREVLINE();
						}
					}
					B[Bomb.co[i].y+f][Bomb.co[i].x].PRINT(Bomb.co[i].y+f, Bomb.co[i].x);
				}
			}
		}


		// esq.
		if (Bomb.co[i].x-f >= 2) {
			if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[1] == true) {
				left = true;
			} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[6] == false && B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] == false) {
				if (left == false) {
					if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[2] == true ) {
						if (Memory.e[2] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x-f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] = true;
						SCORE(Bomb.co[i].y, Bomb.co[i].x-f);
						RANDOMITEM(Bomb.co[i].y, Bomb.co[i].x-f);
						if (Bomb.co[i].y == Bomberball.co.y-1 && Bomb.co[i].x-f == Bomberball.co.x) {
                            if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] == false) {
                                Memory = B[Bomb.co[i].y-f][Bomb.co[i].x-f];
                            } else {
                                Memory.ZERO();
                            }
                        }
						if (SuperBombMode == false) {
							left = true;
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[3] == true) {
						if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[9] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x-f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] = true;

						if (SuperBombMode == false) {
							left = true;
						}

					} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[5] == true) {
						if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[9] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x-f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] = true;
						SCORE(Bomb.co[i].y, Bomb.co[i].x-f);
						j = B[Bomb.co[i].y][Bomb.co[i].x-f].mslot;
						Monster.life[j]--;
						if (Stage % 5 ==0 && j == 0) {
						    if (Monster.life[j] == 0) {
						        B[11][14].ZERO();
						    } else {
                                B[11][14].NUMBER(Monster.life[j], 15);
						    }
						    B[11][14].PRINT(11, 14);
						}
						if (Monster.life[j] == 0) {
                            Monster.inboard--;
						}
						if (SuperBombMode == false) {
							left = true;
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[4] == true) {
						if (TimeBombMode == false) {
                            int j;
                            for (j = 0; j < 9; j++) {
                                if (Bomb.co[j].y == Bomb.co[i].y && Bomb.co[j].x == Bomb.co[i].x-f) {
                                    Bomb.start[j] = Bomb.start[i];
                                    Bomb.framenumber[j] = Bomb.framenumber[i];
                                    BOMB(j);
                                }
                            }
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[8] == true && InvencibleMode == false) {
						DIE();
					} else if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[9] == false) {
						if (f == Bomb.fire) {
							B[Bomb.co[i].y][Bomb.co[i].x-f].FIRELEFT();
						} else {
							B[Bomb.co[i].y][Bomb.co[i].x-f].FIREHLINE();
						}
					}
					B[Bomb.co[i].y][Bomb.co[i].x-f].PRINT(Bomb.co[i].y, Bomb.co[i].x-f);
				}
			}
		}

		//direita
		if (Bomb.co[i].x+f <= 12) {
			if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[1] == true) {
				right = true;
			} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[6] == false && B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] == false) {
				if (right == false) {
					if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[2] == true ) {
						if (Memory.e[2] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x+f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] = true;
						SCORE(Bomb.co[i].y, Bomb.co[i].x+f);
						RANDOMITEM(Bomb.co[i].y, Bomb.co[i].x+f);
						if (Bomb.co[i].y == Bomberball.co.y-1 && Bomb.co[i].x+f == Bomberball.co.x) {
                            if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] == false) {
                                Memory = B[Bomb.co[i].y][Bomb.co[i].x+f];
                            } else {
                                Memory.ZERO();
                            }
                        }

						if (SuperBombMode == false) {
							right = true;
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[3] == true) {
						if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[9] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x+f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] = true;

						if (SuperBombMode == false) {
							right = true;
						}

					} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[5] == true) {
						if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[9] == false) {
                            B[Bomb.co[i].y][Bomb.co[i].x+f].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] = true;
						SCORE(Bomb.co[i].y, Bomb.co[i].x+f);
						j = B[Bomb.co[i].y][Bomb.co[i].x+f].mslot;
						Monster.life[j]--;
						if (Stage % 5 ==0 && j == 0) {
						    if (Monster.life[j] == 0) {
						        B[11][14].ZERO();
						    } else {
                                B[11][14].NUMBER(Monster.life[j], 15);
						    }
						    B[11][14].PRINT(11, 14);
						}
						if (Monster.life[j] == 0) {
                            Monster.inboard--;
						}
						if (SuperBombMode == false) {
							right = true;
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[4] == true) {
						if (TimeBombMode == false) {
                            int j;
                            for (j = 0; j < 9; j++) {
                                if (Bomb.co[j].y == Bomb.co[i].y && Bomb.co[j].x == Bomb.co[i].x+f) {
                                    Bomb.start[j] = Bomb.start[i];
                                    Bomb.framenumber[j] = Bomb.framenumber[i];
                                    BOMB(j);
                                }
                            }
						}
					} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[8] == true && InvencibleMode == false) {
						DIE();
					} else if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[9] == false) {
						if (f == Bomb.fire) {
							B[Bomb.co[i].y][Bomb.co[i].x+f].FIRERIGHT();
						} else {
							B[Bomb.co[i].y][Bomb.co[i].x+f].FIREHLINE();
						}
					}
					B[Bomb.co[i].y][Bomb.co[i].x+f].PRINT(Bomb.co[i].y, Bomb.co[i].x+f);
				}
			}
		}
	}
}

//desenhos do fogo, reto
void stage::FIREREMOVE(int i) {
	int f;

	for (f = 1;f <= Bomb.fire; f++) {
		//para cima
		if (Bomb.co[i].y-f >= 2) {
			if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == true ) {
				B[Bomb.co[i].y-f][Bomb.co[i].x].ZERO();
				if (Bomb.co[i].y-f == Bomberball.co.y-1 && Bomb.co[i].x == Bomberball.co.x) {
				    B[Bomb.co[i].y-f][Bomb.co[i].x].BOMBERBALL(Bomberball.color, 0, LastMove);
				}
				B[Bomb.co[i].y-f][Bomb.co[i].x].PRINT(Bomb.co[i].y-f, Bomb.co[i].x);
			}
		}
		//baixo
		if (Bomb.co[i].y+f <= 12) {
			if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] == true ) {
				B[Bomb.co[i].y+f][Bomb.co[i].x].ZERO();
				if (Bomb.co[i].y+f == Bomberball.co.y-1 && Bomb.co[i].x == Bomberball.co.x) {
				    B[Bomb.co[i].y+f][Bomb.co[i].x].BOMBERBALL(Bomberball.color, 0, LastMove);
				}
				B[Bomb.co[i].y+f][Bomb.co[i].x].PRINT(Bomb.co[i].y+f, Bomb.co[i].x);
			}
		}
		//esq.
		if (Bomb.co[i].x-f >= 2) {
			if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] == true ) {
				B[Bomb.co[i].y][Bomb.co[i].x-f].ZERO();
				if (Bomb.co[i].y == Bomberball.co.y-1 && Bomb.co[i].x-f == Bomberball.co.x) {
				    B[Bomb.co[i].y][Bomb.co[i].x-f].BOMBERBALL(Bomberball.color, 0, LastMove);
				}
				B[Bomb.co[i].y][Bomb.co[i].x-f].PRINT(Bomb.co[i].y, Bomb.co[i].x-f);
			}
		}
		//direita
		if (Bomb.co[i].x+f <= 12) {
			if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] == true ) {
				B[Bomb.co[i].y][Bomb.co[i].x+f].ZERO();
				if (Bomb.co[i].y == Bomberball.co.y-1 && Bomb.co[i].x+f == Bomberball.co.x) {
				    B[Bomb.co[i].y][Bomb.co[i].x+f].BOMBERBALL(Bomberball.color, 0, LastMove);
				}
				B[Bomb.co[i].y][Bomb.co[i].x+f].PRINT(Bomb.co[i].y, Bomb.co[i].x+f);
			}
		}
	}
	//centro de explosão
	B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
}

void stage::GAME() {
	int i, j, k;

	//posição inicial (2, 2)
	Bomberball.co.SET(2, 2);

	//posição do bomberball(sprite)
	LastMove = KEY_DOWN;

	// Mostra a inexistencia do portal
	Gate = false;
	//5 minutos
	Time[0] = 5;
	Time[1] = Time[2] = 0;

	//zera memória
	Memory.BOARDS(Color);
	Memory2.ZERO();

	//sem bombas no tabuleiro
	Bomb.inboard = 0;

	for (i = 0; i < 9; i++) {
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
				B[i][j].BOARDS(Color);
			//Blocks
			} else if (i%2 == 1 && j%2 == 1) {
				B[i][j].BLOCK(NR, Color, 0);
				//e[1] = bloco inquebravel
				B[i][j].e[0] = true;
				B[i][j].e[1] = true;
			}
		}
	}

	//bomberball
	B[1][2].HERO(Bomberball.color, LastMove);
	B[2][2].BODY(Bomberball.color, LastMove);

	//imprime quantidade de vidas
	B[0][1].NUMBER(Bomberball.life, 15);
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

    //Limpa as vidas do chefão
    B[10][14].ZERO();
    B[11][14].ZERO();

	//Fase
	//L10N: Eng
	if (Language == '1') {
		B[2][0].LETTER('S', Color);
		B[3][0].LETTER('T', Color);
		B[4][0].LETTER('A', Color);
		B[5][0].LETTER('G', Color);
		B[6][0].LETTER('E', Color);
		B[8][0].NUMBER((Stage-1)/5+1, Color);
		B[9][0].LETTER('|', Color);
		B[10][0].NUMBER((Stage-1)%5+1, Color);
	//Português
	} else {
		B[2][0].LETTER('F', Color);
		B[3][0].LETTER('A', Color);
		B[4][0].LETTER('S', Color);
		B[5][0].LETTER('E', Color);
		B[7][0].NUMBER((Stage-1)/5+1, Color);
		B[8][0].LETTER('|', Color);
		B[9][0].NUMBER((Stage-1)%5+1, Color);
	}


	//verifica as coordenadas dos blocos vazios para random de monstros
	k = 0 ;
	for (i = 2; i < 13; i++) {
		for (j = 2; j < 13; j++) {
			//se o bloco for vazio
			if (B[i][j].e[0] == false || B[i][j].e[8] == true) {
				Randommonster[k] = i*15 + j;
				k++;
			}
		}
	}

	if (Stage % 5 == 0) {
	    BOSS();
	    B[10][14].BOSS(Color);
	    B[11][14].NUMBER(Monster.life[0], 15);
	    B[11][14].DOT('x', 15, 0, 21);
    } else {
        RANDOMMONSTER(Level);
	}

	PRINT();

	gotoxy(1,50);
	textcolor(15);

	//English
	if (Language == '1') {
		printf("\nPress:\nDirectional Keys to move\n1 to use bomb\n2 to punch\n3 to use timebomb\nENTER to pause");
	//Português
	} else {
		printf("\nPressione:\nTeclas Direcionais para mover\n1 para soltar bomba\n2 para socar a bomba\n3 para usar a bomba relogio\nENTER para pausar");
	}
	//fim tabuleiro testes

	//iguala start time a hora atual
	MonsterTime = StartTime = BossTime = clock();
	//duração de cada map: 5 minutos (em segundos)
	TotalTime = 5*60;

	//entrada de controles, enquanto tiver vivo
	while (Stage == ActualStage && Bomberball.life == ActualLife && TotalTime > 0) {
		//limpa buffer teclado
		rewind (stdin);

		//se nenhuma tecla for apertada
		if (!kbhit()) {
			//se não houver mais monstros imprime o portal uma vez
			if (Monster.inboard == 0 && Gate == false){
				RANDOMGATE();
			}

			//se houver bombas no tabuleiro
			if (Bomb.inboard > 0) {
				// se passar a duração de um frame de 0,2 segundos
				for (i = 0; i < 9; i++) {
					if (Bomb.used[i] == true) {
						if (clock() - Bomb.start[i] >= 0.2 * CLOCKS_PER_SEC) {
                            BOMB(i);
                        }
					}
				}
			}

			//se passarem 20 segundos após o invenciblemode
			if (InvencibleMode == true) {
				if (clock() - InvencibleStart >= 20 * CLOCKS_PER_SEC) {
					InvencibleMode = false;//desativa
					B[3][14].ZERO();
					B[3][14].PRINT(3, 14);
				}
			}

			//se a diferença entre a hora atual e do começo do jogo for maior ou igual a 1 segundo
			if (clock() - StartTime >= 1 * CLOCKS_PER_SEC) {
				//imprima o relógio
				TIME();
				//move a cada segundo
				for (i = 0; i < Monster.total; i++) {
                    if (Monster.life[i] > 0 && Monster.type[i] == '3') {
                        HUNTERMOVE(i);
                    } else if (Monster.life[i] > 0 && Monster.type[i] == '1') {
                        RANDOMMOVE(i);
                    }
				}
			}

			//move a cada 0,5 segundo
			if (clock() - MonsterTime >= 0.5 * CLOCKS_PER_SEC){
			    for (i = 0; i < Monster.total; i++) {
                    if (Monster.life[i] > 0 && Monster.type[i] == '4') {
                        HUNTERMOVE(i);
                    }  else if (Monster.life[i] > 0 && Monster.type[i] == '2') {
                        RANDOMMOVE(i);
                    }
				}
				MonsterTime = clock();
            }

            //move de acordo com a velocidade do boss
            if (clock() - BossTime >= BossSpeed * CLOCKS_PER_SEC){
			    for (i = 0; i < Monster.total; i++) {
                    if (Monster.life[i] > 0 && (Monster.type[i] == '5' || Monster.type[i] == '6' || Monster.type[i] == '7')) {
                        BOSSMOVE(i);
                    }
				}
				BossTime = clock();
            }
		} else {
			CONTROL();
		}
	}
}

//efeitos dos items
void stage::ITEM(int i, int j) {
	//som para item
	sound = FSOUND_Sample_Load (2, "sons\\Pegando Item.wav", 0, 0, 0);
	FSOUND_PlaySound (2, sound);
	FSOUND_SetVolume(2, 255);

	if (B[i][j].item == 'f') {
		if (Bomb.fire < 9) {
			Bomb.fire++;
			B[0][3].NUMBER(Bomb.fire, 15);
			B[0][3].PRINT(0, 3);
		}
	} else if (B[i][j].item == 'b') {
		if (Bomb.total < 9) {
			Bomb.total++;
			B[0][5].NUMBER(Bomb.total,15);
			B[0][5].PRINT(0,5);
		}
	} else if (B[i][j].item == 'p') {
		BombPunchMode = true;
		B[6][14].PUNCHIT();
		B[6][14].PRINT(6, 14);
	} else if (B[i][j].item == 'w') {
		WallCrossMode = true;
		B[2][14].WALLIT();
		B[2][14].PRINT(2, 14);
	} else if (B[i][j].item == 'l') {
		if (Bomberball.life<9) {
			Bomberball.life++;
			ActualLife++;
			B[0][1].NUMBER(Bomberball.life, 15);
			B[0][1].PRINT(0,1);
		}
	} else if (B[i][j].item == 'B') {
		SuperBombMode = true;
		B[4][14].SBOMBIT();
		B[4][14].PRINT(4, 14);
	} else if(B[i][j].item == 'F') {
		SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT();
		B[5][14].PRINT(5,14);
	} else if (B[i][j].item == 'i') {
		InvencibleMode = true;
		B[3][14].INVENCIBLEIT();
		B[3][14].PRINT(3, 14);
		InvencibleStart = clock();
	} else if (B[i][j].item == 'k') {
		BombKickMode = true;
		B[7][14].KICKIT();
		B[7][14].PRINT(7, 14);
	} else if (B[i][j].item == 't') {
		TimeBombMode = true;
		B[8][14].TBOMBIT();
		B[8][14].PRINT(8, 14);
	}
}

void stage::MONSTERMOVE(int i, char move) {
	int down, right;
	down = right = 0;

	if (move == KEY_UP) {
        down = -1;
    } else if (move == KEY_DOWN) {
        down = 1;
    } else if (move == KEY_LEFT) {
        right = -1;
    } else if (move == KEY_RIGHT) {
        right = 1;
    }

    if((move == KEY_UP && Monster.co[i].y > 2 ) || (move == KEY_DOWN && Monster.co[i].y < 12) || (move == KEY_LEFT && Monster.co[i].x > 2) || (move == KEY_RIGHT && Monster.co[i].x < 12)) {
        //não atravessa bomba
        if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[4] == false) {
            //só mexe com item/nada/bomberball
            if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[0] == false || B[Monster.co[i].y+down][Monster.co[i].x+right].e[3] == true || B[Monster.co[i].y+down][Monster.co[i].x+right].e[8] == true) {
                B[Monster.co[i].y][Monster.co[i].x].ZERO();
                B[Monster.co[i].y][Monster.co[i].x].PRINT(Monster.co[i].y, Monster.co[i].x);

                if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[8] == true) {
                    if (InvencibleMode == false) {
                        DIE();
                    }
                }

                if (Monster.type[i] == '5' || Monster.type[i] == '6' || Monster.type[i] == '7') {
                    B[Monster.co[i].y+down][Monster.co[i].x+right].BOSS(Color);
                } else {
                     B[Monster.co[i].y+down][Monster.co[i].x+right].MONSTER(Monster.type[i]);
                }
                B[Monster.co[i].y+down][Monster.co[i].x+right].mslot = i;
                B[Monster.co[i].y+down][Monster.co[i].x+right].PRINT(Monster.co[i].y+down, Monster.co[i].x+right);

                if (move == KEY_UP || move == KEY_DOWN) {
                    Monster.co[i].y += down;
                } else {
                    Monster.co[i].x += right;
                }
            }
        }
    }
}

void stage::RANDOMMOVE(int i) {
    char move;
    move = rand() % 4;
    switch(move) {
        case 0: move = KEY_UP; break;
        case 1: move = KEY_DOWN; break;
        case 2: move = KEY_LEFT; break;
        case 3: move = KEY_RIGHT;
    }
    MONSTERMOVE(i, move);
}

void stage::MOVE() {
	int down, right;
	down = right = 0;

	if (Key == KEY_UP ) {
		down = -1;
	} else if (Key == KEY_DOWN) {
		down = 1;
	} else if (Key == KEY_LEFT) {
		right = -1;
	} else if (Key == KEY_RIGHT) {
		right = 1;
	}
    if (B[Bomberball.co.y+down][Bomberball.co.x+right].e[4] == false ) {
        if (WallCrossMode == true || (WallCrossMode == false && B[Bomberball.co.y+down][Bomberball.co.x+right].e[2] == false) || B[Bomberball.co.y+down][Bomberball.co.x+right].e[6] == true) {
            if((Key == KEY_UP && Bomberball.co.y > 2 ) || (Key == KEY_DOWN && Bomberball.co.y < 12) || (Key == KEY_LEFT && Bomberball.co.x > 2) || (Key == KEY_RIGHT && Bomberball.co.x < 12)) {
                //se for portal
                if (B[Bomberball.co.y+down][Bomberball.co.x+right].e[6] == true) {
                    ActualStage++;
                //se não for bloco quebrável
                } else if (B[Bomberball.co.y+down][Bomberball.co.x+right].e[1] == false) {
                    B[Bomberball.co.y-1][Bomberball.co.x] = Memory;
                    B[Bomberball.co.y][Bomberball.co.x] = Memory2;
                    B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
                    B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);

                    if (B[Bomberball.co.y+down][Bomberball.co.x+right].e[3] == true) {
                        if (LastMove == KEY_DOWN) {
                             Memory = Memory2;
                             Memory2.ZERO();
                        } else {
                            Memory = B[Bomberball.co.y+down-1][Bomberball.co.x+right];
                            Memory2.ZERO();
                        }
                        ITEM(Bomberball.co.y+down,Bomberball.co.x+right);
                    } else {
                        if (LastMove == KEY_UP) {
                             Memory2 = Memory;
                             Memory = B[Bomberball.co.y+down-1][Bomberball.co.x+right];

                        } else if (LastMove == KEY_DOWN) {
                             Memory = Memory2;
                             Memory2 = B[Bomberball.co.y+down][Bomberball.co.x+right];
                        } else {
                            Memory = B[Bomberball.co.y+down-1][Bomberball.co.x+right];
                            Memory2 = B[Bomberball.co.y+down][Bomberball.co.x+right];
                        }
                    }

                    //se houver um monstro ou fogo
                    if (B[Bomberball.co.y+down][Bomberball.co.x+right].e[5] == true || B[Bomberball.co.y+down][Bomberball.co.x+right].e[7] == true) {
                         if (LastMove == KEY_UP) {
                             Memory2 = Memory;
                             Memory.ZERO();
                        } else if (LastMove == KEY_DOWN) {
                             Memory.ZERO();
                             Memory2.ZERO();
                        } else {
                            Memory = B[Bomberball.co.y+down-1][Bomberball.co.x+right];
                            Memory2.ZERO();
                        }
                        if (InvencibleMode == false) {
                            if (Key == 72 || Key == 80) {//atualiza a posição do bomberball
                                Bomberball.co.y += down;
                            } else {
                                Bomberball.co.x += right;
                            }
                            DIE();
                            if (Key == KEY_UP || Key == KEY_DOWN) {//volta ao anterior para continuar a função
                                Bomberball.co.y -= down;
                            } else {
                                Bomberball.co.x -= right;
                            }
                        }
                    } else {
                        B[Bomberball.co.y+down-1][Bomberball.co.x+right].HERO(Bomberball.color, LastMove);
                        B[Bomberball.co.y+down][Bomberball.co.x+right].BODY(Bomberball.color, LastMove);
                    }

                    B[Bomberball.co.y+down-1][Bomberball.co.x+right].PRINT(Bomberball.co.y+down-1, Bomberball.co.x+right);
                    B[Bomberball.co.y+down][Bomberball.co.x+right].PRINT(Bomberball.co.y+down, Bomberball.co.x+right);

                    if (Key == KEY_UP || Key == KEY_DOWN) {
                        Bomberball.co.y += down;
                    } else {
                        Bomberball.co.x += right;
                    }
                    //imprime outra sprite do bomberball
                } else {
                    B[Bomberball.co.y-1][Bomberball.co.x].HERO(Bomberball.color, LastMove);
                    B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
                    B[Bomberball.co.y][Bomberball.co.x].BODY(Bomberball.color, LastMove);
                    B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);
                }
            } else {
                B[Bomberball.co.y-1][Bomberball.co.x].HERO(Bomberball.color, LastMove);
                B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
                B[Bomberball.co.y][Bomberball.co.x].BODY(Bomberball.color, LastMove);
                B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);

            }
        } else {
            B[Bomberball.co.y-1][Bomberball.co.x].HERO(Bomberball.color, LastMove);
            B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
            B[Bomberball.co.y][Bomberball.co.x].BODY(Bomberball.color, LastMove);
            B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);
        }
    } else {
       B[Bomberball.co.y-1][Bomberball.co.x].HERO(Bomberball.color, LastMove);
       B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
       B[Bomberball.co.y][Bomberball.co.x].BODY(Bomberball.color, LastMove);
       B[Bomberball.co.y][Bomberball.co.x].PRINT(Bomberball.co.y, Bomberball.co.x);
       if (BombKickMode == true) {
            int i;
            i = B[Bomberball.co.y+down][Bomberball.co.x+right].bslot;
            BOMBKICK(i);
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
	A[4][7].BOMBERBALL(15, 0, KEY_DOWN);
	A[5][6].DOT(DR, 15, 0, 15);
	A[5][6].DOT(UR, 13, 0, 24);
	A[5][7].VLINE(NR, 1, 0, 2);
	A[5][7].VLINE(NR, 1, 0, 3);
	A[5][7].VLINE(NR, 1, 0, 4);
	A[5][7].DOT(UR, 15, 0, 11);
	A[5][7].DOT(UR, 15, 0, 15);
	A[5][7].DOT(DR, 0, 1, 22);
	A[5][7].DOT(DR, 14, 1, 23);
	A[5][7].DOT(DR, 0, 1, 24);
	A[5][8].DOT(DR, 15, 0, 11);
	A[5][8].DOT(UR, 13, 0, 22);
	A[6][7].DOT(NR, 15, 0, 12);
	A[6][7].DOT(NR, 15, 0, 14);
	A[6][7].DOT(DR, 13, 15, 22);
	A[6][7].DOT(DR, 13, 15, 24);

	//itens
	A[8][4].FIREIT();
	A[8][6].LIFEIT();
	A[8][8].BOMBIT();
	A[8][10].KICKIT();
	A[9][3].PUNCHIT();
	A[9][5].WALLIT();
	A[9][7].INVENCIBLEIT();
	A[9][9].SBOMBIT();
	A[9][11].SFIREIT();


	//limpa tela
	system("cls");

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
	bool x;
	char ch;

	B[14][0].LETTER('!', 12);
	B[14][1].LETTER('P', 12);
	B[14][2].LETTER('A', 12);
	B[14][3].LETTER('U', 12);
	B[14][4].LETTER('S', 12);
	B[14][5].LETTER('E', 12);
	for (j = 6; j < 15; j++) {
		B[14][j].LETTER(' ', 0);
	}
	for(j = 0; j < 15; j++) {
		B[14][j].PRINT(14, j);
	}

	ch = getch();
	// limpa as letras do console de cheats de trás para frente
	for(j = 13; j >= 0; j--) {
		B[14][j+1].ZERO();
		B[14][j+1].PRINT(14, j+1);
	}
	j = 0;
	while (ch != KEY_START && j < 14) {
		Pass[j] = ch;
		B[14][j+1].LETTER(Pass[j], 15);
		B[14][j+1].PRINT(14, j+1);
		ch = getch();
		j++;
	}

	while (j < 14) {
		Pass[j] = '\0';
		j++;
	}

	x = false;
	if (strcmp(Pass, "invencible") == 0  || strcmp(Pass, "INVENCIBLE") == 0){
		InvencibleMode = true;
		InvencibleStart = clock();
		B[3][14].INVENCIBLEIT();
		B[3][14].PRINT(3, 14);
		x = true;
	} else if (strcmp(Pass, "superbomb") == 0 || strcmp(Pass, "SUPERBOMB") == 0) {
		SuperBombMode = true;
		B[4][14].SBOMBIT();
		B[4][14].PRINT(4, 14);
		x = true;
	} else if (strcmp(Pass, "wallcross") == 0 || strcmp(Pass, "WALLCROSS") == 0) {
		WallCrossMode = true;
		B[2][14].WALLIT();
		B[2][14].PRINT(2, 14);
		x = true;
	} else if (strcmp(Pass, "superfire") == 0 || strcmp(Pass, "SUPERFIRE") == 0) {
		SuperFireMode = true;
		Bomb.fire = 9;
		B[0][3].NUMBER(Bomb.fire, 15);
		B[0][3].PRINT(0, 3);
		B[5][14].SFIREIT();
		B[5][14].PRINT(5,14);
		x = true;
	} else if (strcmp(Pass, "stageup") == 0 || strcmp(Pass, "STAGEUP") == 0){
		ActualStage++;
		x = true;
	} else if (strcmp(Pass, "maxlife") == 0 || strcmp(Pass, "MAXLIFE") == 0) {
		ActualLife = 9;
		Bomberball.life = 9;
		B[0][1].NUMBER(Bomberball.life, 15);
		B[0][1].PRINT(0, 1);
		x = true;
	} else if (strcmp(Pass, "maxbomb") == 0 || strcmp(Pass, "MAXBOMB") == 0) {
		Bomb.total = 9;
		B[0][5].NUMBER(Bomb.total, 15);
		B[0][5].PRINT(0, 5);
		x = true;
	} else if (strcmp(Pass, "bombpunch") == 0 || strcmp(Pass, "BOMBPUNCH") == 0){
		BombPunchMode = true;
		B[6][14].PUNCHIT();
		B[6][14].PRINT(6, 14);
		x = true;
	} else if (strcmp(Pass, "bombkick") == 0 || strcmp(Pass, "BOMBKICK") == 0){
		BombKickMode = true;
		B[7][14].KICKIT();
		B[7][14].PRINT(7, 14);
		x = true;
	} else if (strcmp(Pass, "timebomb") == 0 || strcmp(Pass, "TIMEBOMB") == 0){
		TimeBombMode = true;
		B[8][14].TBOMBIT();
		B[8][14].PRINT(8, 14);
		x = true;
	}

	if (x == true) {// se algum cheat der certo
		B[14][0].LETTER('!', 14);
		B[14][0].PRINT(14, 0);
		for (j = 0; j < 14; j++) {
			B[14][j+1].LETTER(Pass[j], 14);
			B[14][j+1].PRINT(14, j+1);
		}
	} else {
		B[14][0].LETTER('!', 15);// se não funcionar
		B[14][0].PRINT(14, 0);
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

void stage::RANDOMGATE() {
	int k;
	do {
		k = rand() % Nullspaces;
	} while (B[Randommonster[k]/15][Randommonster[k]%15].e[0] == true);
	B[Randommonster[k]/15][Randommonster[k]%15].GATE();
	B[Randommonster[k]/15][Randommonster[k]%15].PRINT(Randommonster[k]/15, Randommonster[k]%15);
	//põe o portal no jogo
	Gate = true;
}

void stage::RANDOMITEM(int i, int j) {
	int k;

	//atribui um valor randômico para k
	k = rand()%100;

	if (Randomitem[k] != '0') {
		B[i][j].ZERO();
		switch (Randomitem[k]) {
			case 'f': B[i][j].FIREIT(); break;
			case 'b': B[i][j].BOMBIT(); break;
			case 'l': B[i][j].LIFEIT(); break;
			case 'w': B[i][j].WALLIT(); break;
			case 'B': B[i][j].SBOMBIT(); break;
			case 'F': B[i][j].SFIREIT(); break;
			case 'p': B[i][j].PUNCHIT(); break;
			case 'k': B[i][j].KICKIT(); break;
			case 'i': B[i][j].INVENCIBLEIT(); break;
			case 't': B[i][j].TBOMBIT();
		}
		B[i][j].PRINT(i, j);
    }
}

void stage::RANDOMMONSTER(int level) {
	int i, k, l;
	for (i = 0; i < Monster.total; i++) {
		do {
			k = rand() % Nullspaces;
			Monster.co[i].y = Randommonster[k]/15;
			Monster.co[i].x = Randommonster[k]%15;
		} while (B[Monster.co[i].y][Monster.co[i].x].e[5] == true || Monster.co[i].y <= 3 || Monster.co[i].x <= 3);
		l = rand() % level + 1;
		// transforma 1 em '1', etc...
		Monster.type[i] = l + 48;
		Monster.life[i] = 1;
		B[Monster.co[i].y][Monster.co[i].x].MONSTER(Monster.type[i]);
		B[Monster.co[i].y][Monster.co[i].x].mslot = i;
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
		if (B[i][j].monster == '1') {
			Point += 100;
		} else if (B[i][j].monster == '2') {
			Point += 200;
		}  else if (B[i][j].monster == '3') {
			Point += 300;
		} else if (B[i][j].monster == '4') {
			Point += 400;
		} else if (B[i][j].monster == '5') {
		    Point += 500;
		} else if (B[i][j].monster == '6') {
		    Point += 600;
		} else {
		    Point += 700;
		}
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
	if (Point >= LifeUp) {
	    Bomberball.life++;
	    ActualLife++;
	    B[0][1].NUMBER(Bomberball.life, 15);
        B[0][1].PRINT(0,1);
	    LifeUp += 10000;
	}
}

void stage::STAGE() {
	int i, j;

	//ugh, pallete swaps
	if (Stage == 1) {
		Color = 11;
		Nullspaces = 61;
		Monster.total = Monster.inboard = 3;
		Level = 1;
	} else if (Stage == 2) {
		Color = 10;
		Nullspaces = 76;
		Monster.total = Monster.inboard = 5;
		Level = 1;
	} else if (Stage == 3) {
		Color = 14;
		Nullspaces = 76;
		Monster.total = Monster.inboard = 5;
		Level = 2;
	} else if (Stage == 4) {
		Color = 13;
		Nullspaces = 72;
		Monster.total = Monster.inboard = 7;
		Level = 2;
	} else if (Stage == 5) {
		Color = 12;
		Nullspaces = 96;
		Monster.total = Monster.inboard = 1;
		Level = 5;
	} else if (Stage == 6) {
		Color = 9;
		Nullspaces = 84;
		Monster.total = Monster.inboard = 5;
		Level = 3;
	} else if (Stage == 7) {
		Color = 2;
		Nullspaces = 85;
		Monster.total = Monster.inboard = 6;
		Level = 3;
	} else if (Stage == 8) {
		Color = 6;
		Nullspaces = 56;
		Monster.total = Monster.inboard = 7;
		Level = 3;
	} else if (Stage == 9) {
		Color = 5;
		Nullspaces = 72;
		Monster.total = Monster.inboard = 8;
		Level = 3;
	} else if (Stage == 10) {
		Color = 4;
		Nullspaces = 96;
		Monster.total = Monster.inboard = 1;
		Level = 6;
	} else if (Stage == 11) {
		Color = 1;
		Nullspaces = 76;
		Monster.total = Monster.inboard = 7;
		Level = 4;
	} else if (Stage == 12) {
		Color = 3;
		Nullspaces = 68;
		Monster.total = Monster.inboard = 8;
		Level = 4;
	} else if (Stage == 13) {
		Color = 7;
		Nullspaces = 65;
		Monster.total = Monster.inboard = 9;
		Level = 4;
	} else if (Stage == 14) {
		Color = 8;
		Nullspaces = 56;
		Monster.total = Monster.inboard = 10;
		Level = 4;
	} else if (Stage == 15) {
		Color = 15;
		Nullspaces = 96;
		Monster.total = Monster.inboard = 1;
		Level = 7;
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
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 2) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (i%2 == 1 && j%2 == 0) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 3) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (j%2 == 1 && i%2 == 0) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 4) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if (i == 3 || i == 11 || j == 3 ||  j== 11) {
					B[i][j].SQBLOCK(Color);
				}
				else if (i > 4 && i < 10 && j > 4 && j < 10) {
					if (i == 5 || i== 9 || j == 5 || j == 9) {
						B[i][j].SQBLOCK(Color);
					}
				}
			}
		}
	} else if (Stage == 6) {
		for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i == 7 || j == 7) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 7) {
		for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 8) {
		for (i = 3; i < 12; i++) {
			for (j = 3; j < 12; j++) {
				if ((i+j) % 2 == 1) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 9) {
	   for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i == 7 || j == 7 || i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 11) {
	    for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
    } else if (Stage == 12) {
	    for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5 || i == 7 || j == 7) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
    } else if (Stage == 13) {
	    for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5 || i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
    } else if (Stage == 14) {
	    for (i = 2; i < 13; i++){
			for (j = 2; j < 13; j++){
				if (i == 6 || i == 8 || j == 6 || j== 8) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
    }

}

void stage::STAGEOP() {
	block A[1][15];
	int j, x;

	textcolor(0);
	system("cls");
	for (j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}
	if (Language == '1') {
		A[0][4].LETTER('S', Color);
		A[0][5].LETTER('T', Color);
		A[0][6].LETTER('A', Color);
		A[0][7].LETTER('G', Color);
		A[0][8].LETTER('E', Color);
		A[0][10].NUMBER((Stage-1)/5+1, Color);
		A[0][11].LETTER('-', Color);
		A[0][12].NUMBER((Stage-1)%5+1, Color);
	} else {
		A[0][4].LETTER('F', Color);
		A[0][5].LETTER('A', Color);
		A[0][6].LETTER('S', Color);
		A[0][7].LETTER('E', Color);
		A[0][9].NUMBER((Stage-1)/5+1, Color);
		A[0][10].LETTER('-', Color);
		A[0][11].NUMBER((Stage-1)%5+1, Color);
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

void stage::END(bool win) {
	block A[1][15];
	int j, x;

	textcolor(0);
	system("cls");
	for (j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}
	if (win == true) {
		if (Language == '1') {
			A[0][4].LETTER('Y', 15);
			A[0][5].LETTER('O', 15);
			A[0][6].LETTER('U', 15);
			A[0][8].LETTER('W', 15);
			A[0][9].LETTER('O', 15);
			A[0][10].LETTER('N', 15);
			A[0][11].LETTER('!', 15);
		} else {
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
	}
	else {
		if (Language == '1') {
			A[0][3].LETTER('Y', 15);
			A[0][4].LETTER('O', 15);
			A[0][5].LETTER('U', 15);
			A[0][7].LETTER('L', 15);
			A[0][8].LETTER('O', 15);
			A[0][9].LETTER('S', 15);
			A[0][10].LETTER('E', 15);
			A[0][11].LETTER('!', 15);
		} else {
			A[0][2].LETTER('V',15);
			A[0][3].LETTER('O', 15);
			A[0][4].LETTER('C', 15);
			A[0][5].LETTER('E', 15);
			A[0][7].LETTER('P',15);
			A[0][8].LETTER('E', 15);
			A[0][9].LETTER('R', 15);
			A[0][10].LETTER('D', 15);
			A[0][11].LETTER('E',15);
			A[0][12].LETTER('U', 15);
			A[0][13].LETTER('!', 15);
		}
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

void stage::BOMBKICK(int i) {

	switch(LastMove) {
		case KEY_DOWN: {
			if (Bomb.co[i].EQUAL(Bomberball.co.x, Bomberball.co.y+1)) {
				//apaga a bomba antiga
				B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
				B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
				while (Bomb.co[i].y+1 <= 12) {
					if(B[Bomb.co[i].y+1][Bomb.co[i].x].e[0] == false || B[Bomb.co[i].y+1][Bomb.co[i].x].e[3] == true) {
						Bomb.co[i].y++;
					}
					else {
						break;
					}
				}
			}
			break;
		} case KEY_RIGHT: {
			if (Bomb.co[i].EQUAL(Bomberball.co.x+1, Bomberball.co.y)) {
				//apaga a bomba antiga
				B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
				B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
				while (Bomb.co[i].x+1 <= 12) {
					if(B[Bomb.co[i].y][Bomb.co[i].x+1].e[0] == false || B[Bomb.co[i].y][Bomb.co[i].x+1].e[3] == true) {
						Bomb.co[i].x++;
					}
					else {
						break;
					}
				}
			}
			break;
		} case KEY_UP: {
			if (Bomb.co[i].EQUAL(Bomberball.co.x, Bomberball.co.y-1)) {
				//apaga a bomba antiga
				B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
				B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
				Memory.ZERO();
                B[Bomberball.co.y-1][Bomberball.co.x].BOMBERBALL(Bomberball.color, 0, LastMove);
                B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
				while (Bomb.co[i].y-1 >= 2) {
					if(B[Bomb.co[i].y-1][Bomb.co[i].x].e[0] == false || B[Bomb.co[i].y-1][Bomb.co[i].x].e[3] == true) {
						Bomb.co[i].y--;
					}
					else {
						break;
					}
				}
			}
			break;
		} case KEY_LEFT: {
			 if (Bomb.co[i].EQUAL(Bomberball.co.x-1, Bomberball.co.y)) {
				//apaga a bomba antiga
				B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
				B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
				while (Bomb.co[i].x-1 >= 2) {
					if(B[Bomb.co[i].y][Bomb.co[i].x-1].e[0] == false || B[Bomb.co[i].y][Bomb.co[i].x-1].e[3] == true) {
						Bomb.co[i].x--;
					}
					else {
						break;
					}
				}
			}
		}
	}
	B[Bomb.co[i].y][Bomb.co[i].x].bslot = i;
}

void stage::BOMBPUNCH(int i) {
	//apaga a bomba antiga
	B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	switch(LastMove) {
		case KEY_DOWN : Bomb.co[i].y = (Bomb.co[i].y%11) + 2; break;
		case KEY_RIGHT : Bomb.co[i].x = (Bomb.co[i].x%11) + 2; break;
		case KEY_UP :
            Memory.ZERO();
            B[Bomberball.co.y-1][Bomberball.co.x].BOMBERBALL(Bomberball.color, 0, LastMove);
            B[Bomberball.co.y-1][Bomberball.co.x].PRINT(Bomberball.co.y-1, Bomberball.co.x);
			if (Bomb.co[i].y == 2 || Bomb.co[i].y == 3) {
				Bomb.co[i].y += 9;
			} else {
				Bomb.co[i].y -= 2;
			} break;
		case KEY_LEFT:
			if (Bomb.co[i].x == 2 || Bomb.co[i].x == 3) {
				Bomb.co[i].x += 9;
			} else {
				Bomb.co[i].x -= 2;
			}
	}
	B[Bomb.co[i].y][Bomb.co[i].x].bslot = i;
}

void stage::CONTINUE() {
	block A[1][15];
	int j, x;

	textcolor(0);
	system("cls");
	for (j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}
	if (Language == '1') {
			A[0][3].LETTER('C', 15);
			A[0][4].LETTER('O', 15);
			A[0][5].LETTER('N', 15);
			A[0][6].LETTER('T', 15);
			A[0][7].LETTER('I', 15);
			A[0][8].LETTER('N', 15);
			A[0][9].LETTER('U', 15);
			A[0][10].LETTER('E', 15);
			A[0][11].LETTER('?', 15);

	} else {
			A[0][3].LETTER('C', 15);
			A[0][4].LETTER('O', 15);
			A[0][5].LETTER('N', 15);
			A[0][6].LETTER('T', 15);
			A[0][7].LETTER('I', 15);
			A[0][8].LETTER('N', 15);
			A[0][9].LETTER('U', 15);
			A[0][10].LETTER('A', 15);
			A[0][11].LETTER('R', 15);
			A[0][12].LETTER('?', 15);
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
}

void stage::HUNTERMOVE(int i) {
    int difx, dify;
    char move;
    difx = Bomberball.co.x - Monster.co[i].x;
    dify = Bomberball.co.y - Monster.co[i].y;
    if (abs(difx) >= abs(dify)) {
        if (difx > 0) {
            if (B[Monster.co[i].y][Monster.co[i].x+1].e[1] == true) {
                if (dify >= 0) {
                    move = KEY_DOWN;
                } else {
                    move = KEY_UP;
                }
            } else {
                move = KEY_RIGHT;
            }

        } else if (difx < 0){
            if (B[Monster.co[i].y][Monster.co[i].x-1].e[1] == true) {
                if (dify >= 0) {
                    move = KEY_DOWN;
                } else {
                    move = KEY_UP;
                }
            } else {
                move = KEY_LEFT;
            }

        } else {
            if (dify > 0) {
                if (B[Monster.co[i].y+1][Monster.co[i].x].e[1] == true) {
                    move = KEY_RIGHT;
                } else {
                    move = KEY_DOWN;
                }

            } else if (dify < 0) {
                if (B[Monster.co[i].y-1][Monster.co[i].x].e[1] == true) {
                    move = KEY_RIGHT;
                } else {
                    move = KEY_UP;
                }

            }
        }
    } else {
        if (dify > 0) {
            if (B[Monster.co[i].y+1][Monster.co[i].x].e[1] == true) {
                if (difx >= 0) {
                    move = KEY_RIGHT;
                } else {
                    move = KEY_LEFT;
                }
            } else {
                move = KEY_DOWN;
            }

        } else if (dify < 0) {
            if (B[Monster.co[i].y-1][Monster.co[i].x].e[1] == true) {
                if (difx >= 0) {
                    move = KEY_RIGHT;
                } else {
                    move = KEY_LEFT;
                }
            } else {
                move = KEY_UP;
            }

        } else {
            if (difx > 0) {
                if (B[Monster.co[i].y][Monster.co[i].x+1].e[1] == true) {
                    move = KEY_DOWN;
                } else {
                    move = KEY_RIGHT;
                }

            } else if (difx < 0) {
                if (B[Monster.co[i].y][Monster.co[i].x-1].e[1] == true) {
                    move = KEY_DOWN;
                } else {
                    move = KEY_LEFT;
                }
            }
        }
    }

    MONSTERMOVE(i, move);
}

void stage::BOSS() {
    int i, k, l;
	for (i = 0; i < Monster.total; i++) {
		do {
			k = rand() % Nullspaces;
			Monster.co[i].y = Randommonster[k]/15;
			Monster.co[i].x = Randommonster[k]%15;
		} while (B[Monster.co[i].y][Monster.co[i].x].e[5] == true || Monster.co[i].y <= 3 || Monster.co[i].x <= 3);
		l = Level;
		if (Stage == 5) {
           BossSpeed = 0.5;
		} else if (Stage == 10) {
		   BossSpeed = 0.35;
        } else {
            BossSpeed = 0.2;
        }
		// transforma 1 em '1', etc...
		Monster.type[i] = l + 48;
		Monster.life[i] = 5;
		B[Monster.co[i].y][Monster.co[i].x].BOSS(Color);
		B[Monster.co[i].y][Monster.co[i].x].mslot = i;
    }
}

void stage::BOSSMOVE(int i) {
    int difx, dify, difx2, dify2, j;
    char move;
    difx = Bomberball.co.x - Monster.co[i].x;
    dify = Bomberball.co.y - Monster.co[i].y;
    move = '0';
    if (Bomb.inboard > 0) {
        for (j = 0; j < 9; j++) {
            if (Bomb.used[j] == true) {
                difx2 = Bomb.co[j].x-Monster.co[i].x;
                dify2 = Bomb.co[j].y-Monster.co[i].y;
                if (Monster.co[i].y == Bomb.co[j].y) {
                    if (B[Monster.co[i].y-1][Monster.co[i].x].e[0] == false) {
                        move = KEY_UP;
                        goto A;
                    } else if (B[Monster.co[i].y+1][Monster.co[i].x].e[0] == false) {
                        move = KEY_DOWN;
                        goto A;
                    } else {
                        if (difx2 < 0) {
                            move = KEY_RIGHT;
                            goto A;
                        } else if (difx2 > 0) {
                            move = KEY_LEFT;
                            goto A;
                        }
                    }
                } else if (Monster.co[i].x == Bomb.co[j].x) {
                    if (B[Monster.co[i].y][Monster.co[i].x-1].e[0] == false) {
                        move = KEY_LEFT;
                        goto A;
                    } else if (B[Monster.co[i].y][Monster.co[i].x+1].e[0] == false) {
                        move = KEY_RIGHT;
                        goto A;
                    } else {
                        if (dify2 < 0) {
                            move = KEY_DOWN;
                            goto A;
                        } else if (dify2 > 0){
                            move = KEY_UP;
                            goto A;
                        }
                    }
                }
            }
        }
    }

    if (abs(difx) >= abs(dify)) {
        if (difx > 0) {
            if (B[Monster.co[i].y][Monster.co[i].x+1].e[1] == true) {
                if (dify >= 0) {
                    if (GO(i, 2, 1) == true) {
                        move = KEY_DOWN;
                    }
                } else {
                    if (GO(i, 2, -1) == true) {
                        move = KEY_UP;
                    }
                }
            } else {
                if (GO(i, 1, 1) == true) {
                    move = KEY_RIGHT;
                }
            }
        } else if (difx < 0){
            if (B[Monster.co[i].y][Monster.co[i].x-1].e[1] == true) {
                if (dify >= 0) {
                    if (GO(i, 2, 1) == true) {
                        move = KEY_DOWN;
                    }
                } else {
                    if (GO(i, 2, -1) == true) {
                        move = KEY_UP;
                    }
                }
            } else {
                if (GO(i, 1, -1) == true) {
                    move = KEY_LEFT;
                }
            }
        } else {
            if (dify > 0) {
                if (B[Monster.co[i].y+1][Monster.co[i].x].e[1] == true) {
                    if (GO(i, 1, 1) == true) {
                        move = KEY_RIGHT;
                    }
                } else {
                    if (GO(i, 2, 1) == true) {
                        move = KEY_DOWN;
                    }
                }
            } else if (dify < 0) {
                if (B[Monster.co[i].y-1][Monster.co[i].x].e[1] == true) {
                    if (GO(i, 1, 1) == true) {
                        move = KEY_RIGHT;
                    }
                } else {
                   if (GO(i, 2, -1) == true) {
                        move = KEY_UP;
                    }
                }

            }
        }
    } else {
        if (dify > 0) {
            if (B[Monster.co[i].y+1][Monster.co[i].x].e[1] == true) {
                if (difx >= 0) {
                    if (GO(i, 1, 1) == true) {
                        move = KEY_RIGHT;
                    }
                } else {
                    if (GO(i, 1, -1) == true) {
                        move = KEY_LEFT;
                    }
                }
            } else {
                if (GO(i, 2, 1) == true) {
                    move = KEY_DOWN;
                }
            }
        } else if (dify < 0) {
            if (B[Monster.co[i].y-1][Monster.co[i].x].e[1] == true) {
                if (difx >= 0) {
                    if (GO(i, 1, 1) == true) {
                        move = KEY_RIGHT;
                    }
                } else {
                    if (GO(i, 1, -1) == true) {
                        move = KEY_LEFT;
                    }
                }
            } else {
                if (GO(i, 2, -1) == true) {
                    move = KEY_UP;
                }
            }
        } else {
            if (difx > 0) {
                if (B[Monster.co[i].y][Monster.co[i].x+1].e[1] == true) {
                    if (GO(i, 2, 1) == true) {
                        move = KEY_DOWN;
                    }
                } else {
                    if (GO(i, 1, 1) == true) {
                        move = KEY_RIGHT;
                    }
                }
            } else if (difx < 0) {
                if (B[Monster.co[i].y][Monster.co[i].x-1].e[1] == true) {
                    if (GO(i, 2, 1) == true) {
                        move = KEY_DOWN;
                    }
                } else {
                    if (GO(i, 1, -1) == true) {
                        move = KEY_LEFT;
                    }
                }
            }
        }
    }

    A:
    if (move != '0') {
        MONSTERMOVE(i, move);
    }
}

//decide se o chefão movimenta ou não
bool stage::GO(int i, int co, int n) {
    int j;
    bool go;
    go = true;
    if (Bomb.inboard > 0) {
        for (j = 0; j < 9; j++) {
            if (Bomb.used[j] == true) {
                if (co == 1) {
                    if(Bomb.co[j].x == Monster.co[i].x+n) {
                        go = false;
                    }
                } else if (co == 2) {
                    if(Bomb.co[j].y == Monster.co[i].y+n) {
                        go = false;
                    }
                }
            }
        }
    }
    return go;
}
