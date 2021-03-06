/*
	Projeto bomball - C�pia barata de bomberman e tetris
	Bomberman: estrutura stage, inclui praticamente todos os elementos

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse c�digo � licenciado para voc� sob os termos da GNU GPL, vers�o 3;
# veja http://www.gnu.org/licenses/gpl.html.

# A biblioteca FMOD est� sendo usada em sua vers�o gratuita (pessonal).
# Veja sua licen�a em http://www.fmod.org/index.php/sales.
*/

typedef struct stage {
	//*** VARI�VEIS ***
	bomb Bomb;

	hero Bomberboy;

	monster Monster;

	// Tabuleiro 15x15
	block B[15][15];

	// Idioma do jogo
	char Language;

	// Cor da fase, pallete swapping
	short int Color;

	// Random
		// Para guardar as probabilidades de aparecer de cada item
		char Randomitem[100];
		// Para guardar as posi��es das casas vazias
		short int Randommonster[100];

	// Tempos
		// Clock do in�cio do jogo e de cada atualiza��o de monstros
		clock_t StartTime, MonsterTime, BossTime;
		short int TotalTime;
		// Tempo para ser exibido
		short int Time[3];
		//clock do in�cio do modo invenc�vel
		clock_t InvencibleStart;

	// Indica se o portal foi impresso
	bool Gate;
	// N�mero do map
	short int Stage;
	// Level dos monstros
	short int Level;
	// Velocidade do chef�o
	float BossSpeed;
	// N�mero de blocos vazios
	short int Nullspaces;
	// Para level up
	short int ActualStage, ActualLife;
	// Para aumentar vida
	short int LifeUp;

	// Modos
	bool InvencibleMode, WallCrossMode, SuperBombMode, SuperFireMode, BombKickMode, BombPunchMode, TimeBombMode;

	// Pontua��es
	int Point;
	short int Score[6];

	// Cheatzors: passwords
	char Pass[14];

	// Movimenta��o
		// Tecla pressionada
		char Key;
		// �ltimo movimento
		char LastMove;
		// Blocos de Mem�ria para movimenta��o
		block Memory, Memory2;

	// Sons
	FSOUND_SAMPLE *sound1, *sound2, *sound3, *sound4, *sound5, *sound6;
	bool Mute;

	// *** FUN��ES ****

	// Bomba
	void BOMB(int i);
	void EXPLOSION(int i);
	void FIREREMOVE(int i);

	// Jogo
	void BEGIN();
	void GAME();
	void STAGE();

	// Infra-estrutura
	void BOMBKICK(int i);
	void BOMBPUNCH(int i);
	void BOSS();
	void DIE();
	void ITEM(int i, int j);
	void PASSWORD();
	void PRINT();
	void SCORE(int i, int j);
	void TIME();

	// Movimenta��o
	void BOSSMOVE(int i);
	void CONTROL();
	bool GO(int i, int co, int n);
	void HUNTERMOVE(int i);
	void MONSTERMOVE(int i, char move);
	void MOVE();
	void RANDOMMOVE(int i);

	// Random
	void RANDOMGATE();
	void RANDOMITEM(int i, int j);
	void RANDOMMONSTER(int level);

	// Texto/mensagens
	void CONTINUE();
	void END(bool win);
	void IMAGES();
	void IMAGES2();
	void OPENING();
	void OPENING2();
	void SHOWPASSWORD();
	void STAGEOP();
};

// *** Bomba ***

// Imprime estados da bomba
void stage::BOMB(int i) {
	if (Bomb.framenumber[i] == 11) {
		// Som para explos�o
		FSOUND_PlaySound (1, sound1);
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

// Explos�o da bomba
void stage::EXPLOSION(int i) {
	bool down, up, left, right;

	down = up = right = left = false;
	// Se o bomberboy estiver em cima da bomba
	if (Bomb.co[i].EQUAL(Bomberboy.co) && InvencibleMode == false) {
		DIE();
	} else if (Bomb.co[i].EQUAL(Bomberboy.co.x, Bomberboy.co.y-1) == false) {
		B[Bomb.co[i].y][Bomb.co[i].x].FIRECENTER();
	}
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	// Aumenta a extens�o da bomba
	for (int f = 1; f < Bomb.fire+1; f++) {

		// Cima
		if (Bomb.co[i].y-f >= 2) {
			if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[1] == true) {
				up = true;
			// N�o coloque sobre portal ou fogo
			} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[6] == false && B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == false) {
				// N�o imprime nas bordas e n�o atravessa blocos
				if (up == false) {
					// Blocos quebr�veis
					if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[2] == true) {
						if (Memory.e[2] == false) {
							B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y-f, Bomb.co[i].x);
						RANDOMITEM(Bomb.co[i].y-f, Bomb.co[i].x);
						if (Bomb.co[i].y-f == Bomberboy.co.y-1 && Bomb.co[i].x == Bomberboy.co.x) {
							if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == false) {
								Memory = B[Bomb.co[i].y-f][Bomb.co[i].x];
							} else {
								Memory.ZERO();
							}
						}
						// Se a superbombmode n�o estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}

					// Itens
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[3] == true) {
						if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[9] == false) {
							B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						// Se a superbombmode n�o estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}

					// Monsters
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[5] == true) {
						if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[9] == false) {
							B[Bomb.co[i].y-f][Bomb.co[i].x].BLOCK(NR, 12, 0);
						}
						B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] = true;
						SCORE(Bomb.co[i].y-f, Bomb.co[i].x);
						int j;
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
						// Se a superbombmode n�o estiver ativada
						if (SuperBombMode == false) {
							up = true;
						}
					// Outra bomba chama a fun��o recursivamente
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[4] == true) {
						if (TimeBombMode == false) {
							for (int j = 0; j < 9; j++) {
								if (Bomb.co[j].y == Bomb.co[i].y-f && Bomb.co[j].x == Bomb.co[i].x) {
									Bomb.start[j] = Bomb.start[i];
									Bomb.framenumber[j] = Bomb.framenumber[i];
									BOMB(j);
								}
							}
						}
					// Se o bomberboy estiver na linha da bomba
					} else if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[8] == true && InvencibleMode == false) {
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

		// Baixo
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
						if (Bomb.co[i].y+f == Bomberboy.co.y-1 && Bomb.co[i].x == Bomberboy.co.x) {
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
						int j;
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
							for (int j = 0; j < 9; j++) {
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

		// Esquerda
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
						if (Bomb.co[i].y == Bomberboy.co.y-1 && Bomb.co[i].x-f == Bomberboy.co.x) {
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
						int j;
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
							for (int j = 0; j < 9; j++) {
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

		// Direita
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
						if (Bomb.co[i].y == Bomberboy.co.y-1 && Bomb.co[i].x+f == Bomberboy.co.x) {
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
						int j;
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
							for (int j = 0; j < 9; j++) {
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

// Desenhos do fogo, reto
void stage::FIREREMOVE(int i) {
	for (int f = 1; f <= Bomb.fire; f++) {
		// Cima
		if (Bomb.co[i].y-f >= 2) {
			if (B[Bomb.co[i].y-f][Bomb.co[i].x].e[7] == true ) {
				B[Bomb.co[i].y-f][Bomb.co[i].x].ZERO();
				if (Bomb.co[i].y-f == Bomberboy.co.y-1 && Bomb.co[i].x == Bomberboy.co.x) {
					B[Bomb.co[i].y-f][Bomb.co[i].x].BOMBERBOY(Bomberboy.color, 0, LastMove);
				}
				B[Bomb.co[i].y-f][Bomb.co[i].x].PRINT(Bomb.co[i].y-f, Bomb.co[i].x);
			}
		}
		// Baixo
		if (Bomb.co[i].y+f <= 12) {
			if (B[Bomb.co[i].y+f][Bomb.co[i].x].e[7] == true ) {
				B[Bomb.co[i].y+f][Bomb.co[i].x].ZERO();
				if (Bomb.co[i].y+f == Bomberboy.co.y-1 && Bomb.co[i].x == Bomberboy.co.x) {
					B[Bomb.co[i].y+f][Bomb.co[i].x].BOMBERBOY(Bomberboy.color, 0, LastMove);
				}
				B[Bomb.co[i].y+f][Bomb.co[i].x].PRINT(Bomb.co[i].y+f, Bomb.co[i].x);
			}
		}
		// Esquerda
		if (Bomb.co[i].x-f >= 2) {
			if (B[Bomb.co[i].y][Bomb.co[i].x-f].e[7] == true ) {
				B[Bomb.co[i].y][Bomb.co[i].x-f].ZERO();
				if (Bomb.co[i].y == Bomberboy.co.y-1 && Bomb.co[i].x-f == Bomberboy.co.x) {
					B[Bomb.co[i].y][Bomb.co[i].x-f].BOMBERBOY(Bomberboy.color, 0, LastMove);
				}
				B[Bomb.co[i].y][Bomb.co[i].x-f].PRINT(Bomb.co[i].y, Bomb.co[i].x-f);
			}
		}
		// Direita
		if (Bomb.co[i].x+f <= 12) {
			if (B[Bomb.co[i].y][Bomb.co[i].x+f].e[7] == true ) {
				B[Bomb.co[i].y][Bomb.co[i].x+f].ZERO();
				if (Bomb.co[i].y == Bomberboy.co.y-1 && Bomb.co[i].x+f == Bomberboy.co.x) {
					B[Bomb.co[i].y][Bomb.co[i].x+f].BOMBERBOY(Bomberboy.color, 0, LastMove);
				}
				B[Bomb.co[i].y][Bomb.co[i].x+f].PRINT(Bomb.co[i].y, Bomb.co[i].x+f);
			}
		}
	}
	// Centro de explos�o
	B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
}

// *** Jogo ***

// Inicializa��o do jogo
void stage::BEGIN() {
	// Inicializando a semente para o random
	srand(time(NULL));

	// Abrindo os arquivos de sons
	Mute = false;
	sound1 = FSOUND_Sample_Load (1, "sons\\explosion.wav", 0, 0, 0);
	sound2 = FSOUND_Sample_Load (2, "sons\\item.wav", 0, 0, 0);
	sound3 = FSOUND_Sample_Load (3, "sons\\bomb.wav", 0, 0, 0);
	sound4 = FSOUND_Sample_Load (4, "sons\\life.wav", 0, 0, 0);
	sound5 = FSOUND_Sample_Load (5, "sons\\stage.wav", 0, 0, 0);
	sound6 = FSOUND_Sample_Load (6, "sons\\die.wav", 0, 0, 0);

	// 50% de chance de n�o ter item
	for (int i = 0; i < 50; i++) {
		Randomitem[i] = '0';
	}

	// 15% de chance de ter bomb item
	for (int i = 50; i < 65; i++) {
		Randomitem[i] = 'b';
	}

	// 15% de chance de ter fire item
	for (int i = 65; i < 80; i++) {
		Randomitem[i] = 'f';
	}

	// 3% de chance de ter punch item
	for (int i = 80; i < 83; i++) {
		Randomitem[i] = 'p';
	}

	// 3% de chance de ter kick item
	for (int i = 83; i < 86; i++) {
		Randomitem[i] = 'k';
	}

	// 3% de chance de ter wall cross item
	for (int i = 86; i < 89; i++) {
		Randomitem[i] = 'w';
	}

	// 3% de chance de ter time bomb item
	for (int i = 89; i < 92; i++) {
		Randomitem[i] = 't';
	}

	// 3% de chance de ter super bomb item
	for (int i = 92; i < 95; i++) {
		Randomitem[i] = 'B';
	}

	// 3% de chance de ter super fire item
	for (int i = 95; i < 98; i++) {
		Randomitem[i] = 'F';
	}

	// 1% de chance de ter life item
	Randomitem[98] = 'l' ;

	// 1% de chance de ter invencible item
	Randomitem[99] = 'i' ;

	// Inicia o stage 1
	Stage = ActualStage = 1;

	// Configura��es iniciais: 3 vidas, bomba e poder de fogo em 1
	Bomberboy.life = ActualLife = 3;
	Bomb.total = Bomb.fire = 1;

	// Pontua��o para ganhar + 1 vida
	LifeUp = 10000;

	// Zera pontua��o
	for (int i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	Point = 0;

	// Inicializa os modos
	WallCrossMode = SuperBombMode = SuperFireMode = InvencibleMode = BombKickMode = BombPunchMode = TimeBombMode = false;

	// Zera mapa
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			B[i][j].ZERO();
		}
	}

	// �cone de vidas
	B[0][0].LIFEIT();
	B[0][1].DOT('x', 15, 0, 21);

	// �cone de fogo
	B[0][2].FIREIT();
	B[0][3].DOT('x', 15, 0, 21);

	// �cone de bomba
	B[0][4].BOMBIT();
	B[0][5].DOT('x', 15, 0, 21);

	// Cheatzor
	B[14][0].LETTER('!',15);
}

// Jogo (fun��o principal)
void stage::GAME() {
	// Posi��o inicial (2, 2)
	Bomberboy.co.SET(2, 2);

	// Posi��o do bomberboy(sprite)
	LastMove = KEY_DOWN;

	// Mostra a inexist�ncia do portal
	Gate = false;

	// 5 minutos
	Time[0] = 5;
	Time[1] = Time[2] = 0;

	// Zera mem�ria da movimenta��o
	Memory.BOARDS(Color);
	Memory2.ZERO();

	// Sem bombas no tabuleiro
	Bomb.inboard = 0;

	for (int i = 0; i < 9; i++) {
		Bomb.used[i] = false;
	}

	// Zera entrada de cheats
	for (int i = 0; i < 14; i++) {
		Pass[i] = '\0';
	}

	for (int i = 1; i < 14; i++) {
		for (int j = 1; j < 14; j++) {
			// Boards
			if (i == 1 || j == 1|| i == 13 || j == 13) {
				B[i][j].BOARDS(Color);
			// Blocks NR
			} else if (i%2 == 1 && j%2 == 1) {
				B[i][j].BLOCK(NR, Color, 0);
				//e[1] = bloco inquebravel
				B[i][j].e[0] = true;
				B[i][j].e[1] = true;
			}
		}
	}

	// Bomberboy
	B[1][2].HERO(Bomberboy.color, LastMove);
	B[2][2].BODY(Bomberboy.color, LastMove);

	// Imprime quantidade de vidas
	B[0][1].NUMBER(Bomberboy.life, 15);
	// Imprime poder de fogo
	B[0][3].NUMBER(Bomb.fire, 15);
	// Imprime quantidade de bombas
	B[0][5].NUMBER(Bomb.total, 15);

	// Imprime tempo INICIAL
	B[0][6].NUMBER(Time[0], Color);
	B[0][7].NUMBER(Time[1], Color);
	B[0][7].DOT(':', Color, 0, 21);
	B[0][8].NUMBER(Time[2], Color);

	// Imprime a pontua��o
	B[0][9].NUMBER(Score[0], 15);
	B[0][10].NUMBER(Score[1], 15);
	B[0][11].NUMBER(Score[2], 15);
	B[0][12].NUMBER(Score[3], 15);
	B[0][13].NUMBER(Score[4], 15);
	B[0][14].NUMBER(Score[5], 15);

	// Limpa as vidas do chef�o
	B[10][14].ZERO();
	B[11][14].ZERO();

	// Fase
	// L10N: Eng
	if (Language == '1' || Language == '3') {
		B[2][0].LETTER('S', Color);
		B[3][0].LETTER('T', Color);
		B[4][0].LETTER('A', Color);
		B[5][0].LETTER('G', Color);
		B[6][0].LETTER('E', Color);
		B[8][0].NUMBER((Stage-1)/5+1, Color);
		B[9][0].LETTER('|', Color);
		B[10][0].NUMBER((Stage-1)%5+1, Color);
	// Portugu�s
	} else {
		B[2][0].LETTER('F', Color);
		B[3][0].LETTER('A', Color);
		B[4][0].LETTER('S', Color);
		B[5][0].LETTER('E', Color);
		B[7][0].NUMBER((Stage-1)/5+1, Color);
		B[8][0].LETTER('|', Color);
		B[9][0].NUMBER((Stage-1)%5+1, Color);
	}


	// Verifica as coordenadas dos blocos vazios para random de monstros
	int k = 0 ;
	for (int i = 2; i < 13; i++) {
		for (int j = 2; j < 13; j++) {
			// Se o bloco for vazio
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

	gotoxy(1, 46);
	textcolor(15);

	// English
	if (Language == '1') {
		printf("\nPress:\nDirectional Keys - to move\n1 - to use bomb\n2 - to punch bomb\n3 - to use timebomb\n4 - mute\nENTER - to pause");
	// Portugu�s
	} else if (Language == '2') {
		printf("\nPressione:\nTeclas Direcionais - para mover\n1 - para soltar bomba\n2 - para socar a bomba\n3 - para usar a bomba relogio\n4 - mudo\nENTER - para pausar");
	// Japon�s
	} else {
		printf("\nOsu:\nHoukou Botan - ugoku\n1 - bon tsukau\n2 - bon tataku\n3 - taimubon tsukau\n4 - mute\nENTER - pause");
	}

	// Iguala start time ao clock atual
	MonsterTime = StartTime = BossTime = clock();
	// Dura��o de cada map: 5 minutos (em segundos)
	TotalTime = 5*60;

	// Entrada de controles, enquanto tiver vivo e n�o esgotar o tempo
	while (Stage == ActualStage && Bomberboy.life == ActualLife && TotalTime > 0) {
		// Se nenhuma tecla for apertada
		if (!kbhit()) {
			// Se n�o houver mais monstros imprime o portal uma vez
			if (Monster.inboard == 0 && Gate == false){
				RANDOMGATE();
			}

			// Se houver bombas no tabuleiro
			if (Bomb.inboard > 0) {
				// Se passar a dura��o de um frame de 0,2 segundo
				for (int i = 0; i < 9; i++) {
					if (Bomb.used[i] == true) {
						if (clock() - Bomb.start[i] >= 0.2 * CLOCKS_PER_SEC) {
							BOMB(i);
						}
					}
				}
			}

			// Se passarem 20 segundos ap�s o invenciblemode
			if (InvencibleMode == true) {
				if (clock() - InvencibleStart >= 20 * CLOCKS_PER_SEC) {
					InvencibleMode = false;//desativa
					B[3][14].ZERO();
					B[3][14].PRINT(3, 14);
				}
			}

			// Se a diferen�a entre a hora atual e do come�o do jogo for maior ou igual a 1 segundo
			if (clock() - StartTime >= 1 * CLOCKS_PER_SEC) {
				// Imprima o rel�gio
				TIME();
				// Move a cada segundo
				for (int i = 0; i < Monster.total; i++) {
					if (Monster.life[i] > 0 && Monster.type[i] == '3') {
						HUNTERMOVE(i);
					} else if (Monster.life[i] > 0 && Monster.type[i] == '1') {
						RANDOMMOVE(i);
					}
				}
			}

			// Move a cada 0,5 segundo
			if (clock() - MonsterTime >= 0.5 * CLOCKS_PER_SEC){
				for (int i = 0; i < Monster.total; i++) {
					if (Monster.life[i] > 0 && Monster.type[i] == '4') {
						HUNTERMOVE(i);
					}  else if (Monster.life[i] > 0 && Monster.type[i] == '2') {
						RANDOMMOVE(i);
					}
				}
				MonsterTime = clock();
			}

			// Move de acordo com a velocidade do chef�o
			if (clock() - BossTime >= BossSpeed * CLOCKS_PER_SEC){
				for (int i = 0; i < Monster.total; i++) {
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

// Personaliza��o de cada fase
void stage::STAGE() {
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

	// Zera o tabuleiro central
	for (int i = 2; i < 13; i++) {
		for (int j = 2; j < 13; j++) {
			B[i][j].ZERO();
		}
	}

	// Tabuleiros
	if (Stage == 1) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i%2 == 0 && j%2 == 0) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 2) {
		for (int i = 3; i < 12; i++) {
			for (int j = 3; j < 12; j++) {
				if (i%2 == 1 && j%2 == 0) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 3) {
		for (int i = 3; i < 12; i++) {
			for (int j = 3; j < 12; j++) {
				if (j%2 == 1 && i%2 == 0) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 4) {
		for (int i = 3; i < 12; i++) {
			for (int j = 3; j < 12; j++) {
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
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i == 7 || j == 7) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 7) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 8) {
		for (int i = 3; i < 12; i++) {
			for (int j = 3; j < 12; j++) {
				if ((i+j) % 2 == 1) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 9) {
	   for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i == 7 || j == 7 || i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 11) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 12) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5 || i == 7 || j == 7) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 13) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i+j == 9 || i+j == 19 || i == j-5 || j == i-5 || i == j || i+j == 14) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	} else if (Stage == 14) {
		for (int i = 2; i < 13; i++){
			for (int j = 2; j < 13; j++){
				if (i == 6 || i == 8 || j == 6 || j== 8) {
					B[i][j].SQBLOCK(Color);
				}
			}
		}
	}
}

// *** Infra-estrutura ***

void stage::BOMBKICK(int i) {
	switch(LastMove) {
		case KEY_DOWN: {
			if (Bomb.co[i].EQUAL(Bomberboy.co.x, Bomberboy.co.y+1)) {
				// Apaga a bomba antiga
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
			if (Bomb.co[i].EQUAL(Bomberboy.co.x+1, Bomberboy.co.y)) {
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
			if (Bomb.co[i].EQUAL(Bomberboy.co.x, Bomberboy.co.y-1)) {
				B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
				B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
				Memory.ZERO();
				B[Bomberboy.co.y-1][Bomberboy.co.x].BOMBERBOY(Bomberboy.color, 0, LastMove);
				B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
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
			 if (Bomb.co[i].EQUAL(Bomberboy.co.x-1, Bomberboy.co.y)) {
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
	// Apaga a bomba antiga
	B[Bomb.co[i].y][Bomb.co[i].x].ZERO();
	B[Bomb.co[i].y][Bomb.co[i].x].PRINT(Bomb.co[i].y, Bomb.co[i].x);
	switch(LastMove) {
		case KEY_DOWN : Bomb.co[i].y = (Bomb.co[i].y%11) + 2; break;
		case KEY_RIGHT : Bomb.co[i].x = (Bomb.co[i].x%11) + 2; break;
		case KEY_UP :
			Memory.ZERO();
			B[Bomberboy.co.y-1][Bomberboy.co.x].BOMBERBOY(Bomberboy.color, 0, LastMove);
			B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
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

// Configura��es do chef�o
void stage::BOSS() {
	int k, l;
	for (int i = 0; i < Monster.total; i++) {
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
		// Transforma 1 em '1', etc...
		Monster.type[i] = l + 48;
		Monster.life[i] = 5;
		B[Monster.co[i].y][Monster.co[i].x].BOSS(Color);
		B[Monster.co[i].y][Monster.co[i].x].mslot = i;
	}
}

// Morte do bomberboy, aproveita e j� imprime o numero de vidas restantes
void stage::DIE() {
	// Som para morte
	FSOUND_PlaySound (6, sound6);
	FSOUND_SetVolume(6, 255);

	// Desabilita todos os efeitos
	WallCrossMode = SuperBombMode = SuperFireMode = InvencibleMode = BombKickMode = BombPunchMode = TimeBombMode = false;
	for (int i = 1; i < 9; i++) {
		B[i][14].ZERO();
		B[i][14].PRINT(i, 14);
	}

	B[Bomberboy.co.y-1][Bomberboy.co.x].BOMBERDIE();
	B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
	B[Bomberboy.co.y][Bomberboy.co.x].BODY(12, LastMove);
	B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);
	if (ActualLife > 0 && ActualLife == Bomberboy.life) {
		ActualLife--;
		B[0][1].NUMBER(ActualLife, 15);
		B[0][1].PRINT(0, 1);
	}
}

// Efeitos dos items
void stage::ITEM(int i, int j) {
	// Som para item
	FSOUND_PlaySound (2, sound2);
	FSOUND_SetVolume(2, 100);

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
		if (Bomberboy.life<9) {
			Bomberboy.life++;
			ActualLife++;
			B[0][1].NUMBER(Bomberboy.life, 15);
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

// Entrada de cheats
void stage::PASSWORD() {
	bool x;
	char ch;

	B[14][0].LETTER('!', 12);
	B[14][1].LETTER('P', 12);
	B[14][2].LETTER('A', 12);
	B[14][3].LETTER('U', 12);
	B[14][4].LETTER('S', 12);
	B[14][5].LETTER('E', 12);
	for (int j = 6; j < 15; j++) {
		B[14][j].LETTER(' ', 0);
	}
	for(int j = 0; j < 15; j++) {
		B[14][j].PRINT(14, j);
	}

	ch = getch();
	// Limpa as letras do console de cheats de tr�s para frente
	for(int j = 13; j >= 0; j--) {
		B[14][j+1].ZERO();
		B[14][j+1].PRINT(14, j+1);
	}
	int j = 0;
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
		Bomberboy.life = 9;
		B[0][1].NUMBER(Bomberboy.life, 15);
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

	// Se algum cheat der certo (amarelo)
	if (x == true) {
		B[14][0].LETTER('!', 14);
		B[14][0].PRINT(14, 0);
		for (j = 0; j < 14; j++) {
			B[14][j+1].LETTER(Pass[j], 14);
			B[14][j+1].PRINT(14, j+1);
		}
	// Se n�o funcionar (branco)
	} else {
		B[14][0].LETTER('!', 15);
		B[14][0].PRINT(14, 0);
	}
}

// Imprima uma linha
void stage::PRINT() {
	for (int i = 0; i < 15; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
				B[i][j].PRINTLINE(x);
			}
			printf("\n");
		}
	}
}

// Calcula pontua��o, aproveita e j� imprime-a
void stage::SCORE(int i, int j) {
	int k;

	// 10 pontos por estourar uma parede
	if (B[i][j].e[2] == true) {
		Point += 10;
	}

	// 100 - 700 pontos por estourar um bicho
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
		Bomberboy.life++;
		ActualLife++;
		B[0][1].NUMBER(Bomberboy.life, 15);
		B[0][1].PRINT(0,1);
		LifeUp += 10000;
		// Som para vida
		FSOUND_PlaySound (4, sound4);
		FSOUND_SetVolume(4, 255);
	}
}

// Imprime o rel�gio
void stage::TIME() {
	TotalTime--;
	if (TotalTime >= 0) {
		// Minutos
		Time[0] = TotalTime/60;
		// Segundos dezenas
		Time[1] = (TotalTime%60)/10;
		// Segundos unidades
		Time[2] = TotalTime%10;

		// Imprima os n�meros
		for (int i = 0; i < 3; i++) {
			B[0][i+6].NUMBER(Time[i], Color);
			B[0][i+6].PRINT(0,i+6);
		}
		StartTime = clock();
	}
}

//*** Movimenta��o ***

// Movimenta��o do chef�o
void stage::BOSSMOVE(int i) {
	int difx, dify, difx2, dify2;
	char move;
	difx = Bomberboy.co.x - Monster.co[i].x;
	dify = Bomberboy.co.y - Monster.co[i].y;
	move = '0';
	if (Bomb.inboard > 0) {
		for (int j = 0; j < 9; j++) {
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


// Controles
void stage::CONTROL() {
	gotoxy(Bomberboy.co.x*5+3, Bomberboy.co.y*3+3);

	Key = getch();
	// Se o cara apertar enter, abra o console de cheat
	if (Key == KEY_START) {
		PASSWORD();

	// Modo mudo ativado/desativado
	} else if (Key == KEY_MUTE) {
		// Ativa/desativa
		Mute = ! Mute;
		for (int i = 0; i < 4; i++) {
			FSOUND_SetMute(i, Mute);
		}

	// Se apertar a bomba rel�gio e estiver ativado o modo timebomb
	} else if (Key == KEY_TBOMB && TimeBombMode == true) {
		if (Bomb.inboard > 0) {
			for (int i = 0; i < 9; i++) {
				if (Bomb.used[i] == true) {
					Bomb.framenumber[i] = 11;
					BOMB(i);
				}
			}
		}

	// Se apertar soco e tiver ativado o modo bombpunch
	} else if (Key == KEY_PUNCH && BombPunchMode == true) {
		switch (LastMove) {
			case KEY_RIGHT: {
				int i;
				if (B[Bomberboy.co.y][Bomberboy.co.x+1].e[4] == true) {
					i = B[Bomberboy.co.y][Bomberboy.co.x+1].bslot;
					BOMBPUNCH(i);
				 }
			}break;
			case KEY_DOWN: {
				int i;
				if (B[Bomberboy.co.y+1][Bomberboy.co.x].e[4] == true) {
					i = B[Bomberboy.co.y+1][Bomberboy.co.x].bslot;
					BOMBPUNCH(i);
				}
			}break;
			case KEY_LEFT: {
				int i;
				if (B[Bomberboy.co.y][Bomberboy.co.x-1].e[4] == true) {
					i = B[Bomberboy.co.y][Bomberboy.co.x-1].bslot;
					BOMBPUNCH(i);
				}
			}break;
			case KEY_UP: {
				int i;
				if (B[Bomberboy.co.y-1][Bomberboy.co.x].e[4] == true) {
					i = B[Bomberboy.co.y-1][Bomberboy.co.x].bslot;
					BOMBPUNCH(i);
				}
			}
		}

	// Caso apertar espa�o e n�o houver outra bomba, nem bloco SQ, solte a bomba
	} else if (Key == KEY_BOMB && Memory2.e[2] == false && B[Bomberboy.co.y][Bomberboy.co.x].e[4] == false  && Bomb.inboard < Bomb.total) {
		for (int i = 0; i < 9; i++) {
			// Se o slot n�o tiver sido usado
			if (Bomb.used[i] == false) {
				Bomb.co[i].SET(Bomberboy.co.x, Bomberboy.co.y);
				Bomb.inboard++;
				Bomb.used[i] = true;
				B[Bomb.co[i].y][Bomb.co[i].x].bslot = i;
				Bomb.start[i] = clock();
				Bomb.framenumber[i] = 1;
				Memory2.ZERO();
				Memory2.bslot = i;
				Memory2.e[4] = true;
				//n�o funciona bombpunch/bombkick
				BOMB(i);
				//som para soltar bomba
				FSOUND_PlaySound (3, sound3);
				FSOUND_SetVolume(3, 60);
				break;
			}
		}

	// Caso apertar bot�es de movimento, mexa-se
	} else if (Key == KEY_UP || Key == KEY_DOWN || Key == KEY_LEFT || Key == KEY_RIGHT) {
		LastMove = Key;
		MOVE();
	}
}

// Decide se o chef�o movimenta ou n�o
bool stage::GO(int i, int co, int n) {
	bool go;
	go = true;
	if (Bomb.inboard > 0) {
		for (int j = 0; j < 9; j++) {
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

// Movimenta��o perseguidora
void stage::HUNTERMOVE(int i) {
	int difx, dify;
	char move;
	difx = Bomberboy.co.x - Monster.co[i].x;
	dify = Bomberboy.co.y - Monster.co[i].y;
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

// Movimenta��o dos monstros/chef�es
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
		// N�o atravessa bomba
		if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[4] == false && B[Monster.co[i].y+down][Monster.co[i].x+right].e[1] == false && B[Monster.co[i].y+down][Monster.co[i].x+right].e[2] == false) {
			// S� mexe com item/nada/bomberboy
			if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[0] == false || B[Monster.co[i].y+down][Monster.co[i].x+right].e[3] == true || B[Monster.co[i].y+down][Monster.co[i].x+right].e[8] == true || B[Monster.co[i].y+down][Monster.co[i].x+right].e[9] == true) {
				B[Monster.co[i].y][Monster.co[i].x].ZERO();
				B[Monster.co[i].y][Monster.co[i].x].PRINT(Monster.co[i].y, Monster.co[i].x);

				if (B[Monster.co[i].y+down][Monster.co[i].x+right].e[8] == true || B[Monster.co[i].y+down][Monster.co[i].x+right].e[8] == true) {
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

// Movimenta��o do her�i
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
	if (B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[4] == false ) {
		if (WallCrossMode == true || (WallCrossMode == false && B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[2] == false) || B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[6] == true) {
			if((Key == KEY_UP && Bomberboy.co.y > 2 ) || (Key == KEY_DOWN && Bomberboy.co.y < 12) || (Key == KEY_LEFT && Bomberboy.co.x > 2) || (Key == KEY_RIGHT && Bomberboy.co.x < 12)) {
				// Se for portal
				if (B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[6] == true) {
					ActualStage++;
				// Se n�o for bloco quebr�vel
				} else if (B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[1] == false) {
					B[Bomberboy.co.y-1][Bomberboy.co.x] = Memory;
					B[Bomberboy.co.y][Bomberboy.co.x] = Memory2;
					B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
					B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);

					if (B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[3] == true) {
						if (LastMove == KEY_DOWN) {
							 Memory = Memory2;
							 Memory2.ZERO();
						} else {
							Memory = B[Bomberboy.co.y+down-1][Bomberboy.co.x+right];
							Memory2.ZERO();
						}
						ITEM(Bomberboy.co.y+down,Bomberboy.co.x+right);
					} else {
						if (LastMove == KEY_UP) {
							 Memory2 = Memory;
							 Memory = B[Bomberboy.co.y+down-1][Bomberboy.co.x+right];

						} else if (LastMove == KEY_DOWN) {
							 Memory = Memory2;
							 Memory2 = B[Bomberboy.co.y+down][Bomberboy.co.x+right];
						} else {
							Memory = B[Bomberboy.co.y+down-1][Bomberboy.co.x+right];
							Memory2 = B[Bomberboy.co.y+down][Bomberboy.co.x+right];
						}
					}

					// Se houver um monstro ou fogo
					if (B[Bomberboy.co.y+down-1][Bomberboy.co.x+right].e[5] == true) {
						Memory.ZERO();
					}
					if (B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[5] == true || B[Bomberboy.co.y+down][Bomberboy.co.x+right].e[7] == true) {
						 if (LastMove == KEY_UP) {
							 Memory2 = Memory;
							 Memory.ZERO();
						} else if (LastMove == KEY_DOWN) {
							 Memory.ZERO();
							 Memory2.ZERO();
						} else {
							Memory = B[Bomberboy.co.y+down-1][Bomberboy.co.x+right];
							Memory2.ZERO();
						}
						if (InvencibleMode == false) {
							if (Key == 72 || Key == 80) {
								// Atualiza a posi��o do Bomberboy
								Bomberboy.co.y += down;
							} else {
								Bomberboy.co.x += right;
							}
							DIE();
							if (Key == KEY_UP || Key == KEY_DOWN) {
								// Volta ao anterior para continuar a fun��o
								Bomberboy.co.y -= down;
							} else {
								Bomberboy.co.x -= right;
							}
						}
					} else {
						B[Bomberboy.co.y+down-1][Bomberboy.co.x+right].HERO(Bomberboy.color, LastMove);
						B[Bomberboy.co.y+down][Bomberboy.co.x+right].BODY(Bomberboy.color, LastMove);
					}

					B[Bomberboy.co.y+down-1][Bomberboy.co.x+right].PRINT(Bomberboy.co.y+down-1, Bomberboy.co.x+right);
					B[Bomberboy.co.y+down][Bomberboy.co.x+right].PRINT(Bomberboy.co.y+down, Bomberboy.co.x+right);

					if (Key == KEY_UP || Key == KEY_DOWN) {
						Bomberboy.co.y += down;
					} else {
						Bomberboy.co.x += right;
					}
					// Imprime outra sprite do Bomberboy
				} else {
					B[Bomberboy.co.y-1][Bomberboy.co.x].HERO(Bomberboy.color, LastMove);
					B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
					B[Bomberboy.co.y][Bomberboy.co.x].BODY(Bomberboy.color, LastMove);
					B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);
				}
			} else {
				B[Bomberboy.co.y-1][Bomberboy.co.x].HERO(Bomberboy.color, LastMove);
				B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
				B[Bomberboy.co.y][Bomberboy.co.x].BODY(Bomberboy.color, LastMove);
				B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);

			}
		} else {
			B[Bomberboy.co.y-1][Bomberboy.co.x].HERO(Bomberboy.color, LastMove);
			B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
			B[Bomberboy.co.y][Bomberboy.co.x].BODY(Bomberboy.color, LastMove);
			B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);
		}
	} else {
	   B[Bomberboy.co.y-1][Bomberboy.co.x].HERO(Bomberboy.color, LastMove);
	   B[Bomberboy.co.y-1][Bomberboy.co.x].PRINT(Bomberboy.co.y-1, Bomberboy.co.x);
	   B[Bomberboy.co.y][Bomberboy.co.x].BODY(Bomberboy.color, LastMove);
	   B[Bomberboy.co.y][Bomberboy.co.x].PRINT(Bomberboy.co.y, Bomberboy.co.x);
	   if (BombKickMode == true) {
			int i;
			i = B[Bomberboy.co.y+down][Bomberboy.co.x+right].bslot;
			BOMBKICK(i);
		}
	}
}

// Movimeta��o rand�mica
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

// *** Random ***

void stage::RANDOMGATE() {
	int k;
	do {
		k = rand() % Nullspaces;
	} while (B[Randommonster[k]/15][Randommonster[k]%15].e[0] == true);
	B[Randommonster[k]/15][Randommonster[k]%15].GATE();
	B[Randommonster[k]/15][Randommonster[k]%15].PRINT(Randommonster[k]/15, Randommonster[k]%15);
	// P�e o portal no jogo
	Gate = true;
}

void stage::RANDOMITEM(int i, int j) {
	int k;

	// Atribui um valor rand�mico para k
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
	int k, l;

	for (int i = 0; i < Monster.total; i++) {
		do {
			k = rand() % Nullspaces;
			Monster.co[i].y = Randommonster[k]/15;
			Monster.co[i].x = Randommonster[k]%15;
		} while (B[Monster.co[i].y][Monster.co[i].x].e[5] == true || Monster.co[i].y <= 3 || Monster.co[i].x <= 3);
		l = rand() % level + 1;
		// Transforma 1 em '1', etc...
		Monster.type[i] = l + 48;
		Monster.life[i] = 1;
		B[Monster.co[i].y][Monster.co[i].x].MONSTER(Monster.type[i]);
		B[Monster.co[i].y][Monster.co[i].x].mslot = i;
	}
}

// *** Texto/mensagens ***
	// system("cls") limpa tela

// Jogar outra vez
void stage::CONTINUE() {
	block A[1][15];

	textcolor(0);
	system("cls");
	for (int j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}
	if (Language == '1' || Language == '3') {
			A[0][2].LETTER('P', 15);
			A[0][3].LETTER('L', 15);
			A[0][4].LETTER('A', 15);
			A[0][5].LETTER('Y', 15);
			A[0][7].LETTER('A', 15);
			A[0][8].LETTER('G', 15);
			A[0][9].LETTER('A', 15);
			A[0][10].LETTER('I', 15);
			A[0][11].LETTER('N', 15);
			A[0][12].LETTER('?', 15);

	} else {
			A[0][1].LETTER('J', 15);
			A[0][2].LETTER('O', 15);
			A[0][3].LETTER('G', 15);
			A[0][4].LETTER('A', 15);
			A[0][5].LETTER('R', 15);
			A[0][7].LETTER('D', 15);
			A[0][8].LETTER('E', 15);
			A[0][10].LETTER('N', 15);
			A[0][11].LETTER('O', 15);
			A[0][12].LETTER('V', 15);
			A[0][13].LETTER('O', 15);
			A[0][14].LETTER('?', 15);
	}

	gotoxy(1, 20);
	for (int x = 1; x < 4; x++) {
		textcolor(0);
		printf("  ");
		for (int j = 0; j < 15; j++) {
			A[0][j].PRINTLINE(x);
		}
	printf("\n");
	}
}

// Encerramento
void stage::END(bool win) {
	block A[1][15];

	textcolor(0);
	system("cls");
	for (int j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}
	if (win == true) {
		if (Language == '1' || Language =='3') {
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
		if (Language == '1' || Language == '3') {
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

	gotoxy(1, 20);
	for (int x = 1; x < 4; x++) {
		textcolor(0);
		printf("  ");
		for (int j = 0; j < 15; j++) {
			A[0][j].PRINTLINE(x);
		}
	printf("\n");
	}
	wait(2000);

	if (win == true) {
		// Sprites/alfabeto/n�meros
		textcolor(0);
		system ("cls");
		IMAGES();
		wait(10000);

		textcolor(0);
		system ("cls");
		IMAGES2();
		wait(10000);

		// Ganha um c�digo
		textcolor(0);
		system ("cls");
		SHOWPASSWORD();
		wait(5000);
	}
}

// Imagens (sprites)
void stage::IMAGES() {
	block A[15][15];

	for(int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
		A[i][j].ZERO();
		}
	}

	A[0][5].LETTER('F', 14);
	A[0][6].LETTER('I', 14);
	A[0][7].LETTER('R', 14);
	A[0][8].LETTER('E', 14);
	A[1][1].FIRECENTER();
	A[1][3].FIREUP();
	A[1][5].FIREDOWN();
	A[1][7].FIRERIGHT();
	A[1][9].FIRELEFT();
	A[1][11].FIREVLINE();
	A[1][13].FIREHLINE();

	A[3][5].LETTER('I', 14);
	A[3][6].LETTER('T', 14);
	A[3][7].LETTER('E', 14);
	A[3][8].LETTER('M', 14);
	A[4][1].SBOMBIT();
	A[4][3].SFIREIT();
	A[4][5].TBOMBIT();
	A[4][7].KICKIT();
	A[4][9].PUNCHIT();
	A[4][11].WALLIT();
	A[4][13].INVENCIBLEIT();
	A[6][3].LIFEIT();
	A[6][5].BOMBIT();
	A[6][7].FIREIT();
	A[6][9].GATE();
	A[6][11].SFIREIT();

	A[8][5].LETTER('H', 14);
	A[8][6].LETTER('E', 14);
	A[8][7].LETTER('R', 14);
	A[8][8].LETTER('O', 14);
	A[9][1].MONSTER1();
	A[9][3].MONSTER2();
	A[9][5].MONSTER3();
	A[9][7].MONSTER4();
	A[9][9].BOSS(12);
	A[9][11].BOSS(4);
	A[9][13].BOSS(15);
	A[11][0].BOMBERDIE();
	A[11][2].HERO(15, KEY_DOWN);
	A[11][4].HERO(14, KEY_DOWN);
	A[11][6].HERO(10, KEY_DOWN);
	A[11][8].HERO(11, KEY_DOWN);
	A[11][10].HERO(8, KEY_DOWN);
	A[11][12].HERO(13, KEY_DOWN);
	A[11][14].BODY(15, KEY_DOWN);

	A[13][5].LETTER('B', 14);
	A[13][6].LETTER('O', 14);
	A[13][7].LETTER('M', 14);
	A[13][8].LETTER('B', 14);
	A[14][0].NBOMB1();
	A[14][2].NBOMB2();
	A[14][4].SBOMB1();
	A[14][6].SBOMB2();
	A[14][8].TBOMB1();
	A[14][10].TBOMB2();
	A[14][12].STBOMB1();
	A[14][14].STBOMB2();

	for (int i = 0; i < 15; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}
}

// Imagens (GUI)
void stage::IMAGES2() {
	block A[15][15];

	for(int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
		A[i][j].ZERO();
		}
	}

	A[0][5].LETTER('L', 14);
	A[0][6].LETTER('E', 14);
	A[0][7].LETTER('T', 14);
	A[0][8].LETTER('T', 14);
	A[0][9].LETTER('E', 14);
	A[0][10].LETTER('R', 14);

	A[1][0].LETTER('A', 15);
	A[1][2].LETTER('B', 15);
	A[1][4].LETTER('C', 15);
	A[1][6].LETTER('D', 15);
	A[1][8].LETTER('E', 15);
	A[1][10].LETTER('F', 15);
	A[1][12].LETTER('G', 15);
	A[1][14].LETTER('H', 15);
	A[3][0].LETTER('I', 15);
	A[3][2].LETTER('J', 15);
	A[3][4].LETTER('K', 15);
	A[3][6].LETTER('L', 15);
	A[3][8].LETTER('M', 15);
	A[3][10].LETTER('N', 15);
	A[3][12].LETTER('O', 15);
	A[3][14].LETTER('P', 15);
	A[5][0].LETTER('Q', 15);
	A[5][2].LETTER('R', 15);
	A[5][4].LETTER('S', 15);
	A[5][6].LETTER('T', 15);
	A[5][8].LETTER('U', 15);
	A[5][10].LETTER('V', 15);
	A[5][12].LETTER('W', 15);
	A[5][14].LETTER('X', 15);
	A[7][0].LETTER('Y', 15);
	A[7][2].LETTER('Z', 15);
	A[7][4].LETTER('!', 15);
	A[7][6].LETTER('?', 15);
	A[7][8].LETTER('-', 15);
	A[7][10].LETTER('|', 15);

	A[9][5].LETTER('N', 14);
	A[9][6].LETTER('U', 14);
	A[9][7].LETTER('M', 14);
	A[9][8].LETTER('B', 14);
	A[9][9].LETTER('E', 14);
	A[9][10].LETTER('R', 14);

	A[10][3].NUMBER(1, 15);
	A[10][5].NUMBER(2, 15);
	A[10][7].NUMBER(3, 15);
	A[10][9].NUMBER(4, 15);
	A[10][11].NUMBER(5, 15);
	A[12][3].NUMBER(6, 15);
	A[12][5].NUMBER(7, 15);
	A[12][7].NUMBER(8, 15);
	A[12][9].NUMBER(9, 15);
	A[12][11].NUMBER(0, 15);

	for (int i = 0; i < 15; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}
}

// Aberturas
void stage::OPENING() {
	block A[10][15];

	for(int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
		A[i][j].ZERO();
		A[i][j].BLOCK(0, 0, 15);
		}
	}

	// Logo da UEL
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

	for (int i = 0; i < 10; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
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
	printf("Ci%cncia da Computa%c%co UEL - 2009", 136, 135, 198);

	gotoxy(1, 35);
}

void stage::OPENING2() {
	block A[10][15];

	for(int i = 0; i < 10; i++) {
		for (int j = 0; j < 15; j++) {
			A[i][j].ZERO();
		}
	}

	A[1][3].LETTER('B', 14);
	A[1][4].LETTER('O', 14);
	A[1][5].LETTER('M', 14);
	A[1][6].LETTER('B', 14);
	A[1][7].LETTER('E', 14);
	A[1][8].LETTER('R', 14);
	A[1][9].LETTER('B', 14);
	A[1][10].LETTER('O', 14);
	A[1][11].LETTER('Y', 14);

	// Bomberboy
	A[3][7].DOT(DR, 13, 0, 33);
	A[4][7].BOMBERBOY(15, 0, KEY_DOWN);
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

	// N�meros e Cores
	A[9][2].NUMBER(1, 8);
	A[9][4].NUMBER(2, 10);
	A[9][6].NUMBER(3, 11);
	A[9][8].NUMBER(4, 13);
	A[9][10].NUMBER(5, 14);
	A[9][12].NUMBER(6, 15);

	system("cls");

	for (int i = 0; i < 10; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}

	gotoxy(1, 35);
}

// Revela um password rand�mico
void stage::SHOWPASSWORD() {
	block A[3][15];
	int k;
	char letter[11];

	textcolor(0);
	system("cls");
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 15; j++) {
			A[i][j].ZERO();
		}
	}

	A[0][3].LETTER('P', 14);
	A[0][4].LETTER('A', 14);
	A[0][5].LETTER('S', 14);
	A[0][6].LETTER('S', 14);
	A[0][7].LETTER('W', 14);
	A[0][8].LETTER('O', 14);
	A[0][9].LETTER('R', 14);
	A[0][10].LETTER('D', 14);

	k = rand()%10;
	switch (k) {
		case 0: strcpy(letter, "MAXLIFE   "); break;
		case 1: strcpy(letter, "MAXBOMB   "); break;
		case 2: strcpy(letter, "SUPERBOMB "); break;
		case 3: strcpy(letter, "SUPERFIRE "); break;
		case 4: strcpy(letter, "INVENCIBLE"); break;
		case 5: strcpy(letter, "STAGEUP   "); break;
		case 6: strcpy(letter, "WALLCROSS "); break;
		case 7: strcpy(letter, "BOMBPUNCH "); break;
		case 8: strcpy(letter, "BOMBKICK  "); break;
		case 9: strcpy(letter, "TIMEBOMB  ");
	}

	for (int i = 0; i < 10; i++) {
		A[2][i+3].LETTER(letter[i], 15);
	}

	system("cls");

	for (int i = 0; i < 3; i++) {
		for (int x = 1; x < 4; x++) {
			textcolor(0);
			printf("  ");
			for (int j = 0; j < 15; j++) {
				A[i][j].PRINTLINE(x);
			}
		printf("\n");
		}
	}

}

// Abertura da fase
void stage::STAGEOP() {
	block A[1][15];

	textcolor(0);
	system("cls");
	for (int j = 0; j < 15; j++) {
		A[0][j].ZERO();
	}

	if (Language == '1' || Language == '3') {
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

	gotoxy(1, 20);
	for (int x = 1; x < 4; x++) {
		textcolor(0);
		printf("  ");
		for (int j = 0; j < 15; j++) {
			A[0][j].PRINTLINE(x);
		}
	printf("\n");
	}

	// Som para abertura
	FSOUND_PlaySound (5, sound5);
	FSOUND_SetVolume(5, 60);

	// Aguarde 2 segundos para iniciar a fase
	wait(2000);
	system("cls");
}
