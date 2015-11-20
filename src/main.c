#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "interface.h"
#include "command.h"
#include "queue.h"
#include "threads.h"


int main(int argc, char** argv){

  static pthread_t thread_serial_id;
  static pthread_t thread_flush_serial;
  static pthread_t thread_commands;

  Queue queue_input;
  Queue queue_output;

  create_queue(&queue_input);
  create_queue(&queue_output);

  int fd_;
  connect_pty (&fd_);

  data_t data = {
    .fd = &fd_, 
    .input = queue_input,
    .output = queue_output,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
  };

  int ret = pthread_create(&thread_serial_id, NULL, serial_simulation,
      &data);
  int ret2 = pthread_create(&thread_flush_serial, NULL, flush_serial,
      &data);
  int ret3 = pthread_create(&thread_commands, NULL, manage_commands,
      &data);

  pthread_join (thread_commands, NULL);
  pthread_join (thread_serial_id, NULL);
  pthread_join (thread_flush_serial, NULL);

  return EXIT_SUCCESS;
}
