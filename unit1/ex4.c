#include <stdio.h>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    puts("Wrong format! Right format: display <absolute-path-to-file>");
    return 1;
  }
  FILE * ptrFilePath;
  ptrFilePath = fopen(argv[1], "r");
  if (!ptrFilePath)
  {
    puts("Unable to open file. Check the path again.");
    return 1;
  }
  int c;
  while ((c = fgetc(ptrFilePath)) != EOF)
  {
    putchar(c);
  }
  fclose(ptrFilePath);
  return 0;
}
