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
	int teste, rotate;
	
	printf("Entre um numero > ");
	scanf("%d", &teste);
	printf("Entre outro numero > ");
	scanf("%d", &rotate);	

    while (teste < 8) {
		Jogo.casas.Limpa(); 
		system("cls");

		Jogo.CriaBloco(teste);
		Jogo.casas.Imprime();

		printf("\n");
		system("pause");
		system("cls");

		Jogo.Queda();
		Jogo.casas.Imprime();

		printf("\n");
		system("pause");
		system("cls");

		Jogo.Gira (teste, rotate);
		Jogo.casas.Imprime();

		printf("\n");
		system("pause");
		system("cls");
		
		printf("Entre um numero > ");
		scanf("%d", &teste);
		printf("Entre outro numero > ");
		scanf("%d", &rotate);			
	}

	printf("\nSaindo!\n");
	system("pause");
}
