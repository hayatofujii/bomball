typedef struct coord {
	short int x;
	short int y;
	void SET (short int column, short int line);
	void SET (coord Coord2);
	bool EQUAL (short int column, short int line);
	bool EQUAL (coord Coord2);
};

//indica as coordenadas x e y
void coord::SET (short int column, short int line) {
	x = column;
	y = line;
}

void coord::SET (coord Coord2) {
	x = Coord2.x;
	y = Coord2.y;
}

//compara duas coordenadas x e duas coordenadas y
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
