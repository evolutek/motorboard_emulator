#include "interface.h"

int connect_pty(int *fd){
  int fd_m, fd_s;
  if(openpty(&fd_m, &fd_s,NULL,NULL,NULL)){
    printf("%sopenpty error...", KRED);
    return -1;
  }
  printf("%sdevice: %s\n",KGRN,ptsname(fd_m));

  login_tty(fd_m);
  *fd = fd_m;

  return 0;
}

uint8_t read_pty(int* fd){
  uint8_t buf = 0;
  int a = read(*fd, &buf,1);
  return buf;
}

int write_pty(int* fd, uint8_t byte){
  int a = write(*fd, &byte, 1);
  return a;
}

int send_to_trajman(int* fd, Queue* out){
  while (!is_empty(out)){
    uint8_t byte_to_send = dequeue(out);
    write_pty(fd, byte_to_send);
  }
}
