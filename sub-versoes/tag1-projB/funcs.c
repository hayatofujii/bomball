/*
	Projeto bomball - Cópia barata de bomberman e tetris
	Tetris: função textcolor, aparentemente da conio.c

Copyright (C) 2009		Ernesto Saito <saitohirai88@gmail.com>
Copyright (C) 2009		Hayato Fujii <hayatofujii@gmail.com>
Copyright (C) 2009		Marcos Rodrigues <morodrigues@yahoo.com.br>

# Esse código é licenciado para você sob os termos da GNU GPL, versão 3;
# veja http://www.gnu.org/licenses/gpl.html.
*/

#include <windows.h>

enum DOS_COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE,
};

void textcolor (DOS_COLORS iColor) {
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}
