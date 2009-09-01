/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Bomberman: estruturas evidentemente utilizadas pelo código principal

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.

# A biblioteca FMOD está sendo usada em sua versão gratuita (pessonal).
# Veja sua licença em http://www.fmod.org/index.php/sales.
*/

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
