#include <stdio.h>
#include <stdlib.h>

/*
roadmap
-> criar os blocos
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board está cheia
-> limpar a linha
-> fazer o resto cair
*/

typedef struct pos {
	int x;
	int y;
};

typedef struct blocos {
	pos b[4];

	void criaI(pos posicao);
	void criaJ(pos posicao);
	void criaL(pos posicao);
	void criaO(pos posicao);
	void criaS(pos posicao);
	void criaT(pos posicao);
	void criaZ(pos posicao);
	
	void giraI();
	void giraJ();
	void giraL();
	void giraO();
	void giraS();
	void giraT();
	void giraZ();
};

typedef struct board {
	int casas[18][10];
	blocos bloco;
	
	void limpaBoard();
	void imprimeBoard();
	void detectaLinhaCheia();
	void limpaLinha();
	void desceLinhas();
};
