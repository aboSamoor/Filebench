#include <stdio.h>
#include <stdlib.h>
int main ()
{
  char number[10] = "3.141592", *end;
  double pi = strtod(number, NULL);
  printf("pi = %lf\n", pi);
  return 0;
}
