#include <stdio.h>
#include <stdlib.h>
#include "funcs.c"

/*
roadmap
-> criar os blocos
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board está cheia
-> limpar a linha
-> fazer o resto cair
*/

#include "board.cpp"

int main (void) {
    board Jogo;
    int teste;

    do {
        printf("Entre um numero > ");
        scanf("%d", &teste);

        Jogo.Limpa(); 
    	Jogo.CriaBloco(teste);
    	Jogo.Imprime();
    	printf("\n\n");
	} while (teste < 8);

	printf("\n\n");
	system("pause");
}
