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

void wait(int milliseconds) {
	clock_t end;
	//soma o número de clock inicial com o número de clocks durante "milliseconds"
	end = clock() + milliseconds * CLOCKS_PER_SEC /1000;
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

void _setcursortype (int type)
{
    CONSOLE_CURSOR_INFO Info;

    Info.dwSize = type;
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE),
      &Info);
}
