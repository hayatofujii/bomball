#include <windows.h>
#include <stdio.h>
#define T 250
int main(){

    printf("\nAt‚ a p‚ nos iremos,...");
    Beep(550,T);
    Beep(495,T);
    Beep(495,2*T);
    Beep(495,T);
    Beep(550,T);
    Beep(495,2*T);
    Beep(330,6*T);

    printf("\b\b\b para o que der e vier.");
    Beep(660,2*T);
    Beep(550,T);
    Beep(495,T);
    Beep(440,2*T);
    Beep(495,T);
    Beep(550,T);
    Beep(495,6*T);

    printf("\nMas o certo, ‚ que n¢s estaremos...");
    Beep(550,T);
    Beep(594,T);
    Beep(660,2*T);
    Beep(634,T);
    Beep(660,T);
    Beep(704,2*T);
    Beep(660,T);
    Beep(704,T);
    Beep(844,2*T);
    Beep(734,4*T);

    printf("\b\b\b com o Grˆmio, onde o Grˆmio estiver!");
    Beep(550,T);
    Beep(594,T);
    Beep(660,2*T);
    Beep(734,T);
    Beep(660,T);
    Beep(495,2*T);
    Beep(594,T);
    Beep(550,T);
    Beep(440,4*T);
}
