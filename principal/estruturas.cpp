typedef struct bomb {
	//clock de in�cio de cada bomba
	clock_t start[9];
	//total de bombas dispon�veis
	int total;
	//bombas no tabuleiro
	int inboard;
	//coordenadas de cada bomba
	coord co[9];
	//frame que ser� executado para cada bomba
	int framenumber[9];
	//pot�ncia do fogo
	int fire;
	//slot usaodo;
	bool used[9];
};

//==============================================

typedef struct monster {
	int life[10];
	int total;
	int inboard;
	char type[10];
	coord co[10];
};

//===============================================

typedef struct hero {
	//n�mero de vidas/continue do bomberball
	int life;
	//coordenadas
	coord co;
	short int color;
};
