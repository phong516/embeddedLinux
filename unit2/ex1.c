#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
  char path[50];
  int offset;
  puts("Path to file: ");
  scanf("%s", path);
  puts("Read offset: ");
  scanf("%d", &offset);
  const int fd = open(path, O_RDONLY);
  if (fd < 0)
  {
    puts("Unable to open file!");
    return 1;
  }
  char buffer[100]; 
  lseek(fd, offset, SEEK_SET);
  read(fd, (char *)buffer, sizeof(buffer));
  puts(buffer);
  close(fd); 
  return 0;
}
