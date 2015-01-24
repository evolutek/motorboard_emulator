#include <stdio.h>
//#include <pty.h>
#include "interface.h"


int main(){
  int fd;
  connect_pty(&fd);
  while (1)
    read_pty(&fd);



    return 0;
}
