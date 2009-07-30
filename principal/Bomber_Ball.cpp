/*
====  ROADMAP block.e====
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
e[12] = timebomb item			tbombit***
e[13] = superbomb item			sbombit
e[14] = superfire item			sfireit
e[15] = invencible item			invencibleit
e[16] = bomberball				  bomberball

Expandível a até e[19], por enquanto.
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "ascidef.c"
#include "funcoes.c"
#include "block.cpp"
#include "stage.cpp"

int main (void) {
	stage S;

	S.BEGIN();
	while (S.Stage <=5) {
		S.STAGE();
		S.GAME();
		if (S.Stage != S.ActualStage) {
			S.Stage++;//vai para a próxima fase
			gotoxy(1, 1);//leva o cursor no começo para impressão
		 }
	}
}
