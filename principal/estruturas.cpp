typedef struct bomb {
	//clock de início de cada bomba
	clock_t start[9];
	//total de bombas disponíveis
	int total;
	//bombas no tabuleiro
	int inboard;
	//coordenadas de cada bomba
	coord co[9];
	//frame que será executado para cada bomba
	int framenumber[9];
	//potência do fogo
	int fire;
	//slot usado;
	bool used[9];
};

//==============================================

typedef struct monster {
	//número de vidas de cada monstro
	int life[10];
	int total;
	int inboard;
	//tipo de monstro (1-7)
	char type[10];
	coord co[10];
};

//===============================================

typedef struct hero {
	int life;
	coord co;
	//cor do bomberball
	short int color;
};
