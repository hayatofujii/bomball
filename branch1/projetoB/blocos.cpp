typedef struct blocos {
	pos min[4];

	void criaI(pos posicao);
	void criaJ(pos posicao);
	void criaL(pos posicao);
	void criaO(pos posicao);
	void criaS(pos posicao);
	void criaT(pos posicao);
	void criaZ(pos posicao);

//	void giraI(int dir);
//	void giraJ(int dir);
//	void giraL(int dir);
//	void giraS(int);
//	void giraT();
//	void giraZ();
};

void blocos::criaI (pos posicao) {
	int cnt;

	for (cnt = 0; cnt < 4; cnt++) {
		min[cnt].setPos(posicao.lin + cnt, posicao.col);
	}
}

void blocos::criaJ (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col);
	min[1].setPos(posicao.lin, posicao.col+1);
	min[2].setPos(posicao.lin, posicao.col+2);
	min[3].setPos(posicao.lin+1, posicao.col+2);
}

void blocos::criaL (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col);
	min[1].setPos(posicao.lin, posicao.col+1);
	min[2].setPos(posicao.lin, posicao.col+2);
	min[3].setPos(posicao.lin+1, posicao.col);
}

void blocos::criaO (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col);
	min[1].setPos(posicao.lin, posicao.col+1);
	min[2].setPos(posicao.lin+1, posicao.col);
	min[3].setPos(posicao.lin+1, posicao.col+1);
}

void blocos::criaO (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col);
	min[1].setPos(posicao.lin, posicao.col+1);
	min[2].setPos(posicao.lin+1, posicao.col);
	min[3].setPos(posicao.lin+1, posicao.col+1);
}

void blocos::criaS (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col+1);
	min[1].setPos(posicao.lin, posicao.col+2);
	min[2].setPos(posicao.lin+1, posicao.col);
	min[3].setPos(posicao.lin+1, posicao.col+1);
}

void blocos::criaT (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col+1);
	min[1].setPos(posicao.lin+1, posicao.col);
	min[2].setPos(posicao.lin+1, posicao.col+1);
	min[3].setPos(posicao.lin+1, posicao.col+2);
}

void blocos::criaZ (pos posicao) {
	min[0].setPos(posicao.lin, posicao.col);
	min[1].setPos(posicao.lin, posicao.col+1);
	min[2].setPos(posicao.lin+1, posicao.col+1);
	min[3].setPos(posicao.lin+1, posicao.col+2);
}
