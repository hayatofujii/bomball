typedef struct bomb {
	//clock de in�cio de cada bomba
	clock_t start[9];
	//total de bombas dispon�veis
	short int total;
	//bombas no tabuleiro
	short int inboard;
	//coordenadas de cada bomba
	coord co[9];
	//frame que ser� executado para cada bomba
	short int framenumber[9];
	//pot�ncia do fogo
	short int fire;
	//slot usado;
	bool used[9];
};

//==============================================

typedef struct monster {
	//n�mero de vidas de cada monstro
	short int life[10];
	short int total;
	short int inboard;
	//tipo de monstro (1-7)
	char type[10];
	coord co[10];
};

//===============================================

typedef struct hero {
	short int life;
	coord co;
	//cor do bomberball
	short int color;
};
