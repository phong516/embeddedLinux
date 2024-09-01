#include <sys/types.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
  printf("Enter PID: ");
  int pid;
  scanf("%d", &pid);
  FILE * ptrProcessFile;
  char path[18];
  sprintf(path, "/proc/%d/status", pid);
  ptrProcessFile = fopen(path, "r");
  if (!ptrProcessFile)
  {
    printf("Unable to open file\n");
    return 1;
  }
  char nameLine[100];
  int c;
  while ((c = fgetc(ptrProcessFile)) != '\t');
  while ((c = fgetc(ptrProcessFile)) != '\n')
  {
    putchar(c);
  }
  putchar('\n'); 

  return 0;
}





