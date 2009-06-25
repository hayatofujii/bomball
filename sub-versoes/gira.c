#include <stdio.h>
#include <time.h>

void sleep ( long milli )
{
  clock_t end, current = clock();
  for( end = current + milli; current < end; current = clock() );
}

int main ( void )
{
  int x = 0;
  const char *barRotate = "|\\-/";
  printf ( "Loading configuration files... " );
  for ( ; ; ) {
    if ( x > 3 ) x = 0;
    printf ( "%c\b", barRotate[x++] );
    sleep ( 200 );
  }
  return 0;
}
