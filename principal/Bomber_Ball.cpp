/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Bomberman: executável principal

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <marokamura@gmail.com>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.

# A biblioteca FMOD está sendo usada em sua versão gratuita (pessonal).
# Veja sua licença em http://www.fmod.org/index.php/sales.
*/

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
	FSOUND_STREAM *backmusic, *backmusic1, *backmusic2, *backmusic3, *backmusic4, *backmusic5;

	// Remove o cursor de impressão
	_setcursortype(1);

	// Inicia o áudio
	FSOUND_Init (44100, 32, 0);

	// Abre os arquivos de músicas
	backmusic1 = FSOUND_Stream_Open("musicas\\op.wma",0, 0, 0);
	backmusic2 = FSOUND_Stream_Open("musicas\\stage0.mp3",0, 0, 0);
	backmusic3 = FSOUND_Stream_Open("musicas\\stage1.mp3",0, 0, 0);
	backmusic4 = FSOUND_Stream_Open("musicas\\stage2.mp3",0, 0, 0);
	backmusic5 = FSOUND_Stream_Open("musicas\\boss.wma",0, 0, 0);

	START:
	// Coloca música de fundo
	backmusic = backmusic1;
	// Repete a música quando acabar
	FSOUND_Stream_SetMode(backmusic, FSOUND_LOOP_NORMAL);
	// Toca a música e ajusta o volume
	FSOUND_Stream_Play (0, backmusic);
	FSOUND_SetVolume(0, 100);

	// UEL
	S.OPENING();
	
	textcolor(15);
	printf("Choose your Language / Escolha seu idioma/ Anata no gengo wo erandekudasai\n\n");
	printf("Press:\n1 - English\n2 - Portuguese\n3 - Japanese\n");

	do {
		S.Language = getch();
	} while (S.Language != '1' && S.Language != '2' && S.Language != '3');

	// Bomberball
	S.OPENING2();

	textcolor(15);
	if (S.Language == '1') {
	// Escolha a cor do seu bomberball
 		printf("Choose your color\n\n");
		textcolor(8); printf("1 - gray\n");
		textcolor(10); printf("2 - green\n");
		textcolor(11); printf("3 - blue\n");
		textcolor(13); printf("4 - pink\n");
		textcolor(14); printf("5 - yellow\n");
		textcolor(15); printf("6 - white\n");
	} else if (S.Language == '2') {
		printf("Escolha sua cor\n\n");
		textcolor(8); printf("1 - cinza\n");
		textcolor(10); printf("2 - verde\n");
		textcolor(11); printf("3 - azul\n");
		textcolor(13); printf("4 - rosa\n");
		textcolor(14); printf("5 - amarelo\n");
		textcolor(15); printf("6 - branco\n");
	} else {
		printf("Anata no iro wo erandekudasai\n\n");
		textcolor(8); printf("1 - haiiro\n");
		textcolor(10); printf("2 - midori\n");
		textcolor(11); printf("3 - aoiro\n");
		textcolor(13); printf("4 - momoiro\n");
		textcolor(14); printf("5 - kiiro\n");
		textcolor(15); printf("6 - shiro\n"); 
	}
	do {
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

	// Fecha a introdução
	FSOUND_Stream_Stop(backmusic1);

	while (S.Stage <= 15 && S.Bomberball.life > 0) {
		S.STAGE();
		// Abertura da fase
		S.STAGEOP();
		if (S.Stage %5 == 0) {
			backmusic = backmusic5;
		} else {
			if (S.Stage < 5) {
				  backmusic = backmusic2;
			} else if (S.Stage < 10) {
				  backmusic = backmusic3;
			} else {
				  backmusic = backmusic4;
			}
		}

		FSOUND_Stream_SetMode(backmusic, FSOUND_LOOP_NORMAL);
		FSOUND_Stream_Play (0, backmusic);
		FSOUND_SetVolume(0, 100);

		S.GAME();

		if (S.Stage != S.ActualStage) {
			FSOUND_Stream_Stop(backmusic);
			// Vai para a próxima fase
			S.Stage++;
		}
		if (S.Bomberball.life != S.ActualLife  || S.TotalTime == 0) {
			FSOUND_Stream_Stop(backmusic);
			// Vai para a mesma fase
			S.Bomberball.life--;
			// Espera um segundo para ver que morreu...
			wait(1000);
		}
	}
	if (S.Stage > 15) {
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
	} else if (S.Language == '2') {
		printf("\t\t\t\t\t1 - sim\n\t\t\t\t\t2 - nao");
	} else {
		printf("\t\t\t\t\t1 - hai\n\t\t\t\t\t2 - iie");
	}
	do {
		S.Key = getch();
	} while(S.Key != '1' && S.Key != '2');
	if (S.Key == '1') {
		system("cls");
		goto START;
	} else {
		// Fecha o áudio
		FSOUND_Stream_Close(backmusic);
		FSOUND_Sample_Free(S.sound1);
		FSOUND_Sample_Free(S.sound2);
		FSOUND_Sample_Free(S.sound3);
		FSOUND_Sample_Free(S.sound4);
		FSOUND_Close();
		return 0;
	 }
}
