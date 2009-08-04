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

	S.OPENING();//uel

	textcolor(15);

	do {
		printf("Choose your Language / Escolha seu idioma\n\n");
		printf("Press:\n1 for English\n2 for Portuguese\n");
		S.Language = getch();
	} while (S.Language != '1' && S.Language != '2');

	S.OPENING2();//bomberball

	do {
		textcolor(15);
		if (S.Language == '1') {
		//escolha a cor do seu bomberball
			printf("Choose your color\n\n");
			textcolor(8); printf("1 for gray\n");
			textcolor(10); printf("2 for green\n");
			textcolor(11); printf("3 for blue\n");
			textcolor(13); printf("4 for pink\n");
			textcolor(14); printf("5 for yellow\n");
			textcolor(15); printf("6 for white\n");
		} else {
			printf("Escolha sua cor\n\n");
			textcolor(8); printf("1 para cinza\n");
			textcolor(10); printf("2 para verde\n");
			textcolor(11); printf("3 para azul\n");
			textcolor(13); printf("4 para rosa\n");
			textcolor(14); printf("5 para amarelo\n");
			textcolor(15); printf("6 para branco\n");
		}
		S.KeyColor = getch();
		switch (S.KeyColor) {
			case '1': S.Bomberball.color = 8; break;
			case '2': S.Bomberball.color = 10; break;
			case '3': S.Bomberball.color = 11; break;
			case '4': S.Bomberball.color = 13; break;
			case '5': S.Bomberball.color = 14; break;
			case '6': S.Bomberball.color = 15;
		}
	} while (S.KeyColor != '1' && S.KeyColor != '2' && S.KeyColor != '3' && S.KeyColor != '4' && S.KeyColor != '5' && S.KeyColor != '6');

	S.BEGIN();

	while (S.Stage <= 5 && S.Bomberball.life > 0  && S.TotalTime > 0) {
		S.STAGE();
        S.STAGEOP();//abertura da fase
        S.GAME();

        if (S.Stage != S.ActualStage) {
            //vai para a pr�xima fase
            S.Stage++;
        }
        if (S.Bomberball.life != S.ActualLife) {
            //vai para a mesma fase
            S.Bomberball.life--;
            wait(1000);//espera um segundo para ver que morreu...
        }
    }
	if (S.Stage > 5) {
        S.END(true);
	}
	if (S.Bomberball.life == 0) {
        S.END(false);
	}
}
