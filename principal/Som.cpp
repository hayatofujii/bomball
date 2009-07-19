#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int main()
{
    printf("Teste\n\n");
    Beep(523,2000); // 523 hertz (C5) e 500 milliseconds
    system("pause");
    
    
    printf("\n\n\nSoltando Bomba\n\n");
    Beep(700,150);
    system("pause");
    
    printf("\n\n\nExplosao\n\n");
    Beep(100,500);
    system("pause");
    
    printf("\n\n\nPegando Itens\n\n");
    Beep(2500,150);
    system("pause");
    
    printf("\n\n\nMorreu\n\n");
    Beep(200,700);
    system("pause");
    
    printf("\n\n\nReady... GO!\n\n");
    Beep(4000,700);
    system("pause");
    
    printf("\n\n\nTime Over!\n\n");
    Beep(3000,400);
    Beep(3000,800);
    system("pause");
    
    system("cls");
    printf("\n\n\tSe vcs acharem melhor mudar algum som ou add, eh soh\n\talterar na frequencia e o tempo dele! ;D naum sei se\n\tvai servir em algo... XD\n\n\n\n");
    system("pause");
    
    return 0;
}
