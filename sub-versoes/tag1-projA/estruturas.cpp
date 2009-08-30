typedef struct bomb {
	//clock de início de cada bomba
	clock_t start[9];
	//total de bombas disponíveis
	short int total;
	//bombas no tabuleiro
	short int inboard;
	//coordenadas de cada bomba
	coord co[9];
	//frame que será executado para cada bomba
	short int framenumber[9];
	//potência do fogo
	short int fire;
	//slot usado;
	bool used[9];
};

//==============================================

typedef struct monster {
	//número de vidas de cada monstro
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
