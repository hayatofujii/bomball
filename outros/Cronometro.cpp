#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

int main ()
{
  int n,i,x;
  i=0;
  printf("\nForneca o tempo de contagem [em minutos] -> ");
  scanf("%d",&x);
  printf("\n\n\n\tREADY....\n\n\n");
  system("pause");
  do{
                  for (n=0; n<60; n++)
                  {
                      system("cls");  
                      printf ("\n\t0%d:%d\n",i,n);
                      wait (1);
                      if(n==59)
                           i++;                         
                      }
                  }while(i<x);
  system("cls");
  printf ("\n\tTIME OVER!!!\n\n\n");
  system("pause");
  return 0;
}
