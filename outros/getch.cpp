#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main ( void )
{
  int ch = getch();

  if ( ch == 0 || ch == 224 )
    ch = getch();

	printf("%d",ch);
printf("\n\n");
system("pause");
return 0;
}
