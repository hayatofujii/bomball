typedef struct coord {
	int x;
	int y;
	void SET (int column, int line);
	void SET (coord Coord2);
	bool EQUAL (int column, int line);
	bool EQUAL (coord Coord2);
};

void coord::SET (int column, int line) {
	x = column;
	y = line;
}

void coord::SET (coord Coord2) {
	x = Coord2.x;
	y = Coord2.y;
}

bool coord::EQUAL (int column, int line) {
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
