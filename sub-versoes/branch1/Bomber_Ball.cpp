/*
====  ROADMAP block.e/stage.Effects ====
e[00] = morte/invencivel		fire/monster
e[01] = bloco inquebravel		block NR
e[02] = bloco quebravel			block SQ/bomb
e[03] = item					fireit/bombit/wallit
e[04] = bomb					bomb
e[05] = monster					monster
e[06] = portal					gate
e[07] = fire					fireup/down/left/right/center
e[08] = fire up item			fireit
e[09] = bomb up item			bombit
e[10] = wall cross item			wallit
e[11] = life up item			lifeit
e[12] = timebomb item			tbombit
e[13] = superbomb item			sbombit
e[14] = superfire item			sfireit
e[15] = invencible item         invencibleit

Expandível a até e[19], por enquanto.
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "conio.c"
#include <time.h>

#include "ascidef.c"
#include "funcoes.c"
#include "block.cpp"
#include "stage.cpp"

int main (void) {
	int i,j,k;
	stage S;

	S.Stage=1;
	S.BEGIN();

	//tabuleiro, para teste
	S.B[2][3].FIREIT(10);
	S.B[2][5].FIREIT(10);
	S.B[2][7].FIREIT(10);
	S.B[2][9].MONSTER();
	S.B[2][11].BOMBIT(10);
	S.B[3][2].BOMBIT(10);
	S.B[4][5].SFIREIT(14);
	S.B[5][2].LIFEIT(10);
	S.B[7][2].WALLIT(14);
	S.B[9][2].INVENCIBLEIT(14);
	S.B[11][2].SBOMBIT(14);
	S.B[12][12].GATE();

	S.B[6][3].FIREIT(10);
	S.B[6][5].FIREIT(10);
	S.B[6][7].FIREIT(10);
	S.B[6][9].FIREIT(10);
	S.B[6][11].FIREIT(10);

	//cheatzor
	S.B[14][0].LETTER('!',15);

	S.PRINT();

	gotoxy(1,50);
	textcolor(15);
	printf("\nPressione:\nW/A/S/D para mover\nSPACE para soltar bomba\nOUTRA tecla para sair");

	i = j = 2;

/*
	//relogio do ernesto aguarde 1 para jogar...
	int l, n;
	l = 1;

	do {
		l--;
		for (n = 60; n >= 0; n--) {
			if (n == 60) {
				S.B[0][6].NUMBER(l,S.Color);
				S.B[0][7].NUMBER(0,S.Color);
				S.B[0][8].NUMBER(0,S.Color);
			} else {
				S.B[0][6].NUMBER(l,S.Color);
				S.B[0][7].NUMBER(n/10,S.Color);
				S.B[0][8].NUMBER(n%10,S.Color);
			}
			S.B[0][6].PRINT(0,6);
			S.B[0][7].PRINT(0,7);
			S.B[0][8].PRINT(0,8);

			wait (1);
			if (n == 0) {
				l--;
			}
		}
	} while(l>=0);
*/

	S.CONTROL(i, j);
}
