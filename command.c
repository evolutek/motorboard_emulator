#include "command.h"

void dispatcher(Queue* q){
  if (q->count > 1){
   // printf("elt: %i", q->head->elt);
    uint8_t count = dequeue(q);
 //   printf("dequeue: %i", count);
/*    t_command command = dequeue(q);

    switch (command){
      case INIT:
        printf("init_sequence");
        break;

      default:
        break;
    }
*/
  }
}

