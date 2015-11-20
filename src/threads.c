#include "threads.h"

void* serial_simulation (void* p_data) {
  data_t* data = (data_t*) p_data;
  int* fd = data->fd;
  while (1) {
    int8_t elt = read_pty (fd);
    pthread_mutex_lock (&data->mutex);
    enqueue (&data->input, elt);
    pthread_mutex_unlock (&data->mutex);
  }
  return NULL;
}

void* flush_serial (void* p_data) {
  data_t* data = (data_t*) p_data;
  int* fd = data->fd;
  while (1) {
    pthread_mutex_lock (&data->mutex);
    if (!is_empty (&data->output))
      send_to_trajman (fd, &data->output);
    pthread_mutex_unlock (&data->mutex);
  }
  return NULL;
}

void* manage_commands (void* p_data) {
  data_t* data = (data_t*) p_data;
  while (1) {
    dispatcher (&data->input, &data->output, &data->mutex);
  }
  return NULL;
}
