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

void wait(float seconds) {
	clock_t end;
	//soma o n�mero de clock inicial com o n�mero de clocks durante "seconds"
	end = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < end);
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
