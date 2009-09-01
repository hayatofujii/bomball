/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Bomberman: estrutura coordenada, só serve para facilitar

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.

# A biblioteca FMOD está sendo usada em sua versão gratuita (pessonal).
# Veja sua licença em http://www.fmod.org/index.php/sales.
*/

typedef struct coord {
	short int x;
	short int y;
	void SET (short int column, short int line);
	void SET (coord Coord2);
	bool EQUAL (short int column, short int line);
	bool EQUAL (coord Coord2);
};

// Indica as coordenadas x e y
void coord::SET (short int column, short int line) {
	x = column;
	y = line;
}

void coord::SET (coord Coord2) {
	x = Coord2.x;
	y = Coord2.y;
}

// Compara duas coordenadas x e duas coordenadas y
bool coord::EQUAL (short int column, short int line) {
	if (x == column && y == line) {
		return true;
	} else {
		return false;
	}
}

bool coord::EQUAL (coord Coord2) {
	if (x == Coord2.x && y == Coord2.y) {
		return true;
	} else {
		return false;
	}
}
