#include <stdio.h>
#include <windows.h>
#include "DeviceDriver.h"

int main() {
  SamsungFlash samsung;
  DeviceDriver dd(&samsung);
  printf("This is Main Function : %d", dd.read(0x1000));

  /*while (1)
  {
          printf("#");
          Sleep(100);
  }*/
  return 0;
}