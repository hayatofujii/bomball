typedef struct bomb {
	// Clock de início de cada bomba
	clock_t start[9];
	// Total de bombas disponíveis
	short int total;
	// Bombas no tabuleiro
	short int inboard;
	// Coordenadas de cada bomba
	coord co[9];
	// Frame que será executado para cada bomba
	short int framenumber[9];
	// Potência do fogo
	short int fire;
	// Slot usado
	bool used[9];
};

//==============================================

typedef struct monster {
	// Número de vidas de cada monstro
	short int life[10];
	short int total;
	short int inboard;
	// Tipo de monstro (1-7)
	char type[10];
	coord co[10];
};

//===============================================

typedef struct hero {
	short int life;
	coord co;
	// Cor do bomberball
	short int color;
};
