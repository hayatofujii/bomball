#include <stdio.h>
#include <stdlib.h>

/*
roadmap
-> criar os blocos
-> fazer eles cairem com o tempo controlado
-> arranjar um jeito de controle
-> detectar quando que uma linha da board está cheia
-> limpar a linha
-> fazer o resto cair
*/

#include "blocos.cpp"

int main (void) {
	blocos Jogo;
	int teste;

    do {
		printf("Entre um numero > ");
		scanf("%d", &teste);

		Jogo.casas.Limpa(); 
		Jogo.CriaBloco(teste);
		Jogo.casas.Imprime();
		printf("\n\n");
		Jogo.Queda();
		Jogo.casas.Imprime();
		printf("\n\n");
	} while (teste < 8);

	printf("\n\n");
	system("pause");
}
