#ifndef _THREADS_H
#define _THREADS_H

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "interface.h"
#include "command.h"
#include "queue.h"


typedef struct {
  int* fd;
  Queue input;
  Queue output;
  pthread_mutex_t mutex;
} data_t;

extern void* serial_simulation (void* p_data);
extern void* flush_serial (void* p_data);
extern void* manage_commands (void* p_data);

#endif /* _THREADS_H */
