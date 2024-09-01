#include <stdio.h>


int main()
{
  FILE *fp;
  fp = fopen("text.txt", "r");
  if (fp == NULL)
  {
    printf("Error! opening file\n");
    return 1;
  }
  int c;
  while ((c = fgetc(fp)) != EOF)
  {
    putchar(c);
  }
  fclose(fp);
  return 0;
}
