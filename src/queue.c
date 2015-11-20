#include "queue.h"

void create_queue(Queue* q){
  q->head = NULL;
  q->tail = NULL;
  q->count = 0;
}

void enqueue(Queue* q, uint8_t elt){
  struct Queue_elt* local_elt = malloc(sizeof(struct Queue_elt));
  local_elt->elt = elt;
  local_elt->pointer = NULL;

  if (q->count == 0){
    q->head = local_elt;
    q->tail = local_elt;
  }
  else{
    q->tail->pointer = local_elt;
    q->tail = local_elt;
  }
  q->count++;
}

uint8_t dequeue (Queue*q){
  if (q->count == 1){
    uint8_t elt = q->head->elt;
    struct Queue_elt* tmp_pointer = q->head;
    q-> head = NULL;
    q-> tail = NULL;
    free (tmp_pointer);
    q->count--;
    return elt;
  } else if (q->count != 0){
    uint8_t elt = q->head->elt;
    struct Queue_elt* tmp_pointer = q->head;
    q->head = tmp_pointer->pointer;
    free (tmp_pointer);
    q->count--;
    return elt;
  }
  else {
    return 0xff;
  }
}

int is_empty(Queue* q){
  if (q->count == 0)
    return 1;
  else {
    return 0;
  }
}

void print_queue(Queue* q){
  printf("> ");
  struct Queue_elt *elt= q->head;
  int i = 0;
  for (i; i<q->count; i++){
    printf("%i:", elt->elt);
    elt = elt->pointer;
  }
  printf("\n");
}

uint8_t queue_head(Queue * q){
  return q->head->elt;
}
