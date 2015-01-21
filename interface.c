#include "interface.h"


int connect_pty(){
  // ask pty
  int pt = posix_openpt(O_RDWR);

  if (pt < 0){
    printf("connection failed...");
    return 1;
  }

  int rc = grantpt(pt);

  if (rc != 0){
    printf("error on grantpt...");
    return 1;
  }

  rc = unlockpt(pt);

  if (rc != 0){
    printf("error on unlockpt...");
    return 1;
  }

}
