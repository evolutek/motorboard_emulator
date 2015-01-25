#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "command.h"
#include <stdint.h>
#include "queue.h"
#include <pthread.h>
#include <unistd.h>


typedef struct{
  Queue input;
  Queue output;
  pthread_mutex_t mutex_queue;
} data_t;


static void* serial_simulation(void * p_data){
  data_t* data = (data_t*)p_data;
  int fd;
  connect_pty(&fd);
  while (1){
   int8_t elt = read_pty(&fd);
   enqueue(&data->input, elt);
   print_queue(&data->input);
  }
  return NULL;
}

static void* manage_commands(void * p_data){
  data_t* data = (data_t*)p_data;
  while(1)
    dispatcher(&data->input);

  return NULL;
}

int main(){

  static pthread_t thread_serial_id;
  static pthread_t thread_commands;

  data_t data;
//  data.mutex_queue = PTHREAD_MUTEX_INITIALIZER;
  create_queue(&data.input);
  create_queue(&data.output);

  int ret = pthread_create(&thread_serial_id, NULL, serial_simulation,
      &data);
  int ret2 = pthread_create(&thread_commands, NULL, manage_commands,
      &data);

  pthread_join(thread_serial_id, NULL);

  return 0;
}
