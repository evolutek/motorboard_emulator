#include "interface.h"

int connect_pty(int *fd){
  int fd_m, fd_s;
  if(openpty(&fd_m, &fd_s,NULL,NULL,NULL)){
    printf("openpty error...");
    return -1;
  }
  printf("device: %s\n",ptsname(fd_m));

  login_tty(fd_m);
  *fd = fd_m;

  return 0;
}

uint8_t read_pty(int* fd){
  uint8_t buf = 0;
  int a = read(*fd, &buf,1);
  return buf;
}
