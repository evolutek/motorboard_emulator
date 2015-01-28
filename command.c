#include "command.h"

float unpackfloat(Queue* q){
  f_conv conv;
  conv.b[0] = dequeue(q);
  conv.b[1] = dequeue(q);
  conv.b[2] = dequeue(q);
  conv.b[3] = dequeue(q);
  return conv.f;
}

void init(Queue *q){
  uint8_t t1 = dequeue(q);
  uint8_t t2 = dequeue(q);
  uint8_t t3 = dequeue(q);
  if (t1 == 170 && t2 == 170 && t3 == 170)
    printf("init sequence grab ! \n");
  else
    printf ("error: init sequence...");
}

void set_diam_wheels(Queue* in){
  printf("diam wheels set \n");
  float g = unpackfloat(in);
  printf("left wheel: %f\n", g);
  float d = unpackfloat(in);
  printf("right wheel: %f\n", g);
}

void set_wheels_spacing(Queue* in){
  printf("wheels spacing set\n");
  float spac = unpackfloat(in);
  printf("spacing: %f\n", spac);
}

void acknowledge(Queue * out){
  enqueue(out, 2);
  enqueue(out, ACKNOWLEDGE);
  printf(" << acknowledge >>\n");
}


void dispatcher(Queue* in, Queue* out, pthread_mutex_t *mutex){
  pthread_mutex_lock(mutex);
  if (!is_empty(in)){
    uint8_t packet_length = queue_head(in);
    if (in->count >= packet_length){
   // printf("elt: %i", q->head->elt);
      uint8_t count = dequeue(in);
      t_command command = dequeue(in);

      switch (command){
        case INIT:
          init(in);
          acknowledge(out);
          break;

        case SET_DIAM_WHEELS:
          set_diam_wheels(in);
          acknowledge(out);
          break;

        case SET_WHEELS_SPACING:
          set_wheels_spacing(in);
          acknowledge(out);
          break;

        case SET_PID_TRSL:
          acknowledge(out);
          break;

        case SET_PID_ROT:
          acknowledge(out);
          break;

        case SET_TRSL_ACC:
          acknowledge(out);
          break;

        case SET_TRSL_DEC:
          acknowledge(out);
          break;

        case SET_TRSL_MAXSPEED:
          acknowledge(out);
          break;

        case SET_ROT_ACC:
          acknowledge(out);
          break;

        case SET_ROT_DEC:
          acknowledge(out);
          break;

        case SET_ROT_MAXSPEED:
          acknowledge(out);
          break;

        case SET_DELTA_MAX_ROT:
          acknowledge(out);
          break;

        case SET_DELTA_MAX_TRSL:
          acknowledge(out);
          break;

        case SET_TELEMETRY:
          acknowledge(out);
          break;

      default:
          break;
      }
    }
  }
  pthread_mutex_unlock(mutex);
}

