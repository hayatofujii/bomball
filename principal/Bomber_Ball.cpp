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

#include "asciidef.c"
#include "funcoes.c"
#include "block.cpp"
#include "stage.cpp"

int main (void) {
	stage S;

	textcolor(15);

	do {
        printf("Choose your Language/ Escolha seu idioma\n\n");
        printf("Press:\n1 for English\n2 for Portuguese\n");
        S.Language = getch();
	} while (S.Language != '1' && S.Language != '2');

	system("cls");//limpa tela

    do {
        if (S.Language == '1') {
            printf("Choose your color\n\n");
            printf("1 for gray\n2 for green\n3 for blue\n4 for pink\n5 for yellow\n6 for white\n");
        } else {
            printf("Escolha sua cor\n\n");
            printf("1 para cinza\n2 para verde\n3 para azul\n4 para rosa\n5 para amarelo\n6 para branco\n");
        }
        S.KeyColor = getch();
        switch (S.KeyColor) {
            case '1': S.BomberballColor = 8; break;
            case '2': S.BomberballColor = 10; break;
            case '3': S.BomberballColor = 11; break;
            case '4': S.BomberballColor = 13; break;
            case '5': S.BomberballColor = 14; break;
            case '6': S.BomberballColor = 15;
        }
	} while (S.KeyColor != '1' && S.KeyColor != '2' && S.KeyColor != '3' && S.KeyColor != '4' && S.KeyColor != '5' && S.KeyColor != '6');

    system("cls");

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
