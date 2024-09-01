#include <stdio.h>
#include <stdint.h>

int main()
{
  FILE * fp;
  fp = fopen("/dev/input/event11", "rb");
  if (!fp)
  {
    puts("/dev/input/event11 is now unavailable");
    return 1;
  }
  struct input 
  {
    uint32_t timevalSecond;
    uint32_t timevalMicroSecond;
    uint16_t type;
    uint16_t code;
    int32_t value;
  }mouseInput;
  int32_t x, y;
  while (fread(&mouseInput, sizeof(mouseInput), 1, fp))
  {
      if (mouseInput.type == 3)
      {
        switch (mouseInput.code)
          {
            case 53:
              x = mouseInput.value;
              break;
            case 54:
              y = mouseInput.value;
              break;
          }
        printf("%d/%d\n", x, y);
      }
  }
  fclose(fp);
  return 0;
}
