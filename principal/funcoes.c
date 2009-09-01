/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Bomberman: funçoes externas, possivelmente da conio.c

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <morodrigues@yahoo.com.br>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.

# A biblioteca FMOD está sendo usada em sua versão gratuita (pessonal).
# Veja sua licença em http://www.fmod.org/index.php/sales.
*/

#include <cstdlib>
#include <iostream>
#include <windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

// Função utilizada para aguardar um intervalo de tempo
void wait(int milliseconds) {
	clock_t end;
	// Soma o número de clock inicial com o número de clocks durante "milliseconds"
	end = clock() + milliseconds * CLOCKS_PER_SEC /1000;
	while (clock() < end);
}

// Função utilizada para mudar o cursor de impressão de lugar
void gotoxy (int coluna, int linha) {
	COORD ponto;
	ponto.X = coluna-1 ;
	ponto.Y = linha-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ponto);
}

// Função utilizada para mudar cor das imagens
void textcolor (int color) {
	__FOREGROUND = color;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
	color + (__BACKGROUND << 4));
}

// Função utilizada para mudar o cursor do teclado
void _setcursortype (int type){
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = type;
	SetConsoleCursorInfo(GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}
