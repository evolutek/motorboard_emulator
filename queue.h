#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Queue_elt{
  uint8_t elt;
  struct Queue_elt* pointer;
};


typedef struct{
  struct Queue_elt* head;
  struct Queue_elt* tail;
  int count;
} Queue;

void create_queue(Queue* q);
void enqueue(Queue* q, uint8_t elt);
uint8_t dequeue();
int is_empty();
void print_queue(Queue* q);

#endif
