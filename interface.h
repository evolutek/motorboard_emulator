#ifndef _INTERFACE_H
#define _INTERFACE_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pty.h>
#include <unistd.h>
#include <utmp.h>
#include <stdint.h>

int connect_pty(int *fd);
uint8_t read_pty(int* fd);


#endif
