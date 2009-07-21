#include <stdio.h>
#include <stdlib.h>

/*
roadmap
-> criar os blocos
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quanto que uma linha da board está cheia
-> limpar a linha
-> fazer o resto cair
*/

typedef struct pos {
	int x;
	int y;
};

typedef struct bloco {
	pos b[4];

	void criaBlocoI(pos posicao);
	void criaBlocoJ(pos posicao);
	void criaBlocoL(pos posicao);
	void criaBlocoO(pos posicao);
	void criaBlocoS(pos posicao);
	void criaBlocoT(pos posicao);
	void criaBlocoZ(pos posicao);
}

typedef struct board {
	int[18][10];
};