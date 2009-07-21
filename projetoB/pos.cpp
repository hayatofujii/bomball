typedef struct pos {
	int lin;
	int col;
	bool full;

	void setPos(int lin, int col);
};

void pos::setPos (int selLin, int selCol) {
	lin = selLin;
	col = selCol;
	full = true;
}
