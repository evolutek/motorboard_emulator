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

int read_pty(int* fd){
  char buf = ' ';
  int a = read(*fd, &buf,1);
  printf("> %x\n", buf);
  return 0;
}
