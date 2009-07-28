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
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void sleep (long dur) {
	clock_t fim, atual;
	atual  = clock();
	for (fim = atual + dur; atual < fim; atual = clock()) {
	}
}

void wait (int dur) {
	clock_t endwait;
	endwait = clock () + dur*CLOCKS_PER_SEC ;
	while (clock() < endwait){
	}
}

void gotoxy (int coluna, int linha) {
	COORD ponto;
	ponto.X = coluna-1 ;
    ponto.Y = linha-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ponto);
}

void textcolor (int color) {
	__FOREGROUND = color;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
	color + (__BACKGROUND << 4));
}
