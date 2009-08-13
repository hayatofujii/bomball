#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "fmod.h"
#include "defines.c"
#include "funcoes.c"
#include "block.cpp"
#include "coord.cpp"
#include "estruturas.cpp"
#include "stage.cpp"


int main (void) {
	stage S;
    FSOUND_STREAM* handle;

	//inicia o audio
	FSOUND_Init (44100, 32, 0);

	//coloca musica de fundo
	handle=FSOUND_Stream_Open("Bass Hunter - Now Youre Gone.mp3",0, 0, 0);
    FSOUND_Stream_Play (0,handle);

    //remove o cursor de impressão(número diferente de 0)
	_setcursortype(1);
	START:
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
			textcolor(8); printf("1 - gray\n");
			textcolor(10); printf("2 - green\n");
			textcolor(11); printf("3 - blue\n");
			textcolor(13); printf("4 - pink\n");
			textcolor(14); printf("5 - yellow\n");
			textcolor(15); printf("6 - white\n");
		} else {
			printf("Escolha sua cor\n\n");
			textcolor(8); printf("1 - cinza\n");
			textcolor(10); printf("2 - verde\n");
			textcolor(11); printf("3 - azul\n");
			textcolor(13); printf("4 - rosa\n");
			textcolor(14); printf("5 - amarelo\n");
			textcolor(15); printf("6 - branco\n");
		}
		S.Key = getch();
		switch (S.Key) {
			case '1': S.Bomberball.color = 8; break;
			case '2': S.Bomberball.color = 10; break;
			case '3': S.Bomberball.color = 11; break;
			case '4': S.Bomberball.color = 13; break;
			case '5': S.Bomberball.color = 14; break;
			case '6': S.Bomberball.color = 15;
		}
	} while (S.Key != '1' && S.Key != '2' && S.Key != '3' && S.Key != '4' && S.Key != '5' && S.Key != '6');

	S.BEGIN();

	while (S.Stage <= 10 && S.Bomberball.life > 0) {
		S.STAGE();
		//abertura da fase
		S.STAGEOP();
		S.GAME();

		if (S.Stage != S.ActualStage) {
			//vai para a próxima fase
			S.Stage++;
		}
		if (S.Bomberball.life != S.ActualLife  || S.TotalTime == 0) {
			//vai para a mesma fase
			S.Bomberball.life--;
			//espera um segundo para ver que morreu...
			wait(1000);
		}
	}
	if (S.Stage > 10) {
		S.END(true);
	}
	if (S.Bomberball.life == 0) {
		S.END(false);
	}

	S.CONTINUE();

	textcolor(15);
	printf("\n\n\n\n");
	if (S.Language == '1') {
	    printf("\t\t\t\t\t1 - yes\n\t\t\t\t\t2 - no");
	} else {
	    printf("\t\t\t\t\t1 - sim\n\t\t\t\t\t2 - nao");
	}
	do {
        S.Key = getch();
	} while(S.Key != '1' && S.Key != '2');
	if (S.Key == '1') {
	    system("cls");
	    goto START;
	}
	return 0;
}
