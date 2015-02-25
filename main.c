#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "command.h"
#include "queue.h"
#include <pthread.h>
#include <unistd.h>


typedef struct{
  Queue input;
  Queue output;
  pthread_mutex_t mutex;
} data_t;


static void* serial_simulation(void * p_data){
  data_t* data = (data_t*)p_data;
  int fd;
  connect_pty(&fd);
  while (1){
   int8_t elt = read_pty(&fd);
    if (data->output.count != 0)
      print_queue(&data->output);
   pthread_mutex_lock(&data->mutex);
   enqueue(&data->input, elt);
   send_to_trajman(&fd, &data->output);
   pthread_mutex_unlock(&data->mutex);
  }
  return NULL;
}

static void* manage_commands(void * p_data){
  data_t* data = (data_t*)p_data;
  while(1){
    dispatcher(&data->input, &data->output, &data->mutex);
  }
  return NULL;
}

int main(){

  static pthread_t thread_serial_id;
  static pthread_t thread_commands;

  Queue queue_input;
  Queue queue_output;

  create_queue(&queue_input);
  create_queue(&queue_output);

  data_t data = {
    .input = queue_input,
    .output = queue_output,
    .mutex = PTHREAD_MUTEX_INITIALIZER,
  };

  int ret = pthread_create(&thread_serial_id, NULL, serial_simulation,
      &data);
  int ret2 = pthread_create(&thread_commands, NULL, manage_commands,
      &data);

  pthread_join(thread_commands, NULL);
  pthread_join(thread_serial_id, NULL);

  return 0;
}
