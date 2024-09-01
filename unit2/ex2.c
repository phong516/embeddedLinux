#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
  DIR * dir = opendir(argv[1]);
  if (!dir)
  {
    puts("Dir not found!");
    return 1;
  }
  struct dirent * dirent;
  struct stat statFile;
  
  while ((dirent = readdir(dir)) != NULL)
  {
    char filePath[512];
    sprintf(filePath, "%s/%s", argv[1], dirent->d_name);
    stat(filePath, &statFile);
    struct tm * timeModified = localtime(&statFile.st_mtim.tv_sec);
    printf("Name: %s Size: %ld Time modified: %s\n", dirent->d_name, statFile.st_size, asctime(timeModified));
  }
  return 0;
}
