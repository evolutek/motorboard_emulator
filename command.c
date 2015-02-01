#include "command.h"

t_robot robot;
s_default defaults;

void packfloat(Queue* q, float f){
  f_conv conv;
  conv.f = f;
  enqueue(q, conv.b[0]);
  enqueue(q, conv.b[1]);
  enqueue(q, conv.b[2]);
  enqueue(q, conv.b[3]);
}

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

void goto_xy(Queue* in){
  float x,y;
  x = unpackfloat(in);
  y = unpackfloat(in);
  printf ("goto x: %f; y: %f\n", x,y);
}

void goto_theta(Queue* in){
  float theta;
  theta = unpackfloat(in);
  printf ("goto theta: %f\n", theta);
}

void execute_free(Queue* in){
  defaults.free = 1;
  printf ("free!\n");
}

void move_trsl(Queue* in){
  float acc, dec, max, dest;
  int sens;
  dest = unpackfloat(in);
  acc = unpackfloat(in);
  dec = unpackfloat(in);
  max = unpackfloat(in);
  sens = dequeue(in);
  sens &= 1;
  sens = (sens == 1) ? 1 : -1;
  printf ("move trsl\n dest: %f; acc: %f; dec: %f; \
    max: %f; sens: %i\n", dest,acc,dest,max,sens);
  /* for emulation
  need to manage over-queuing (cf. motor board code)
  */
}

void move_rot(Queue* in){
  float acc, dec, max, dest;
  int sens;
  dest = unpackfloat(in);
  acc = unpackfloat(in);
  dec = unpackfloat(in);
  max = unpackfloat(in);
  sens = dequeue(in);
  sens &= 1;
  sens = (sens == 1) ? 1 : -1;
  printf ("move rot\n dest: %f; acc: %f; dec: %f; \
    max: %f; sens: %i\n", dest,acc,dest,max,sens);
  /* for emulation
  need to manage over-queuing (cf. motor board code)
  */
}

void set_x(Queue* in){
  float x = unpackfloat(in);
  robot.xpos = x;
  printf ("set x: %f\n", x);
}

void set_y(Queue* in){
  float y = unpackfloat(in);
  robot.ypos = y;
  printf ("set y: %f\n", y);
}

void set_theta(Queue* in){
  float angle = 0;
  float angle_tmp = unpackfloat(in);
  if (!isnan(angle_tmp)){
    float d = floor(angle_tmp/(2.f*PI))+
      ((angle_tmp/(2.f*PI))<0)? 1.f : 0.f ;
    float angle = angle_tmp - d * 2.f *PI;
    if (angle > PI)
      angle -= 2.f* PI;
    else if (angle < -PI)
      angle += 2.f* PI;
  }
  robot.theta = angle;
  printf ("set theta: %f\n", angle);
}

void set_pwm(Queue* in){
  float f1 = unpackfloat(in);
  float f2 = unpackfloat(in);
  printf ("set pwm\n");
}

void set_diam_wheels(Queue* in){
  printf("diam wheels set \n");
  float g = unpackfloat(in);
  robot.diamG = g;
  printf("left wheel: %f\n", g);
  float d = unpackfloat(in);
  robot.diamD = d;
  printf("right wheel: %f\n", g);
}

void set_wheels_spacing(Queue* in){
  printf("wheels spacing set\n");
  float spac = unpackfloat(in);
  robot.distroues = spac;
  printf("spacing: %f\n", spac);
}

void set_pid_trsl(Queue* in){
  printf("pid translation okay\n");
  float p = unpackfloat(in);
  float i = unpackfloat(in);
  float d = unpackfloat(in);
  printf("p: %f; i: %f; d: %f\n", p,i,d);
}

void set_pid_rot(Queue* in){
  printf("pid rotation okay\n");
  float p = unpackfloat(in);
  float i = unpackfloat(in);
  float d = unpackfloat(in);
  printf("p: %f; i: %f; d: %f\n", p,i,d);
}

void set_trsl_acc(Queue* in){
  printf("translation acceleration okay\n");
  float acc = unpackfloat(in);
  defaults.trsl_acc = acc;
  printf("acc: %f\n", acc);
}

void set_trsl_dec(Queue* in){
  printf("translation dec okay\n");
  float dec = unpackfloat(in);
  defaults.trsl_dec = dec;
  printf("dec: %f\n", dec);
}

void set_trsl_max(Queue* in){
  printf("translation max speed okay\n");
  float max = unpackfloat(in);
  defaults.trsl_max = max;
  printf("max: %f\n", max);
}

void set_rot_acc(Queue* in){
  printf("rotation acceleration okay\n");
  float acc = unpackfloat(in);
  defaults.rot_acc = acc;
  printf("acc: %f\n", acc);
}

void set_rot_dec(Queue* in){
  printf("rotation dec okay\n");
  float dec = unpackfloat(in);
  defaults.rot_dec = dec;
  printf("dec: %f\n", dec);
}

void set_rot_max(Queue* in){
  printf("rotation max speed okay\n");
  float max = unpackfloat(in);
  defaults.rot_max = max;
  printf("max: %f\n", max);
}

void set_delta_max_rot(Queue* in){
  printf("delta max rotation okay\n");
  float max = unpackfloat(in);
  defaults.delta_trsl_max;
  printf("max: %f\n", max);
}

void set_delta_max_trsl(Queue* in){
  printf("delta max translation okay\n");
  float max = unpackfloat(in);
  defaults.delta_rot_max;
  printf("max: %f\n", max);
}

void stop_asap(Queue* in){
  printf("stop asap\n");
  unpackfloat(in);
  unpackfloat(in);
}

void set_telemetry(Queue* in){
  printf("telemetry activated\n");
  uint8_t status = dequeue(in);
  defaults.time = 0;
  defaults.telemetry = status;
  printf("status: %i\n", status);
}

void set_debug(Queue* in){
  defaults.time = 0;
  defaults.debug = dequeue(in);
}

void acknowledge(Queue * out){
  enqueue(out, 2);
  enqueue(out, ACKNOWLEDGE);
  printf(" << acknowledge >>\n");
}

void send_error(Queue* out, t_errors error){
  enqueue(out, 3);
  enqueue(out, ERROR);
  enqueue(out, error);
  printf(" << error send >>\n");
}


void dispatcher(Queue* in, Queue* out, pthread_mutex_t *mutex){
  pthread_mutex_lock(mutex);
  if (!is_empty(in)){
    uint8_t packet_length = queue_head(in);
    if (in->count >= packet_length){
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
          set_pid_trsl(in);
          acknowledge(out);
          break;
        case SET_PID_ROT:
          set_pid_rot(in);
          acknowledge(out);
          break;
        case SET_TRSL_ACC:
          set_trsl_acc(in);
          acknowledge(out);
          break;
        case SET_TRSL_DEC:
          set_trsl_dec(in);
          acknowledge(out);
          break;
        case SET_TRSL_MAXSPEED:
          set_trsl_max(in);
          acknowledge(out);
          break;
        case SET_ROT_ACC:
          set_rot_acc(in);
          acknowledge(out);
          break;
        case SET_ROT_DEC:
          set_rot_dec(in);
          acknowledge(out);
          break;
        case SET_ROT_MAXSPEED:
          set_rot_max(in);
          acknowledge(out);
          break;
        case SET_DELTA_MAX_ROT:
          set_delta_max_rot(in);
          acknowledge(out);
          break;
        case SET_DELTA_MAX_TRSL:
          set_delta_max_trsl(in);
          acknowledge(out);
          break;
        case SET_PWM:
          set_pwm(in);
          acknowledge(out);
          break;
        case SET_X:
          set_x(in);
          acknowledge(out);
          break;
        case SET_Y:
          set_y(in);
          acknowledge(out);
          break;
        case SET_THETA:
          set_theta(in);
          acknowledge(out);
          break;
        case SET_TELEMETRY:
          set_telemetry(in);
          acknowledge(out);
          break;
        case SET_DEBUG:
          set_debug(in);
          acknowledge(out);
          break;
        case GOTO_XY:
          goto_xy(in);
          acknowledge(out);
          break;
        case GOTO_THETA:
          goto_theta(in);
          acknowledge(out);
          break;
        case FREE:
          execute_free(in);
          acknowledge(out);
          break;
        case STOP_ASAP:
          stop_asap(in);
          acknowledge(out);
          break;
        case MOVE_TRSL:
          move_trsl(in);
          acknowledge(out);
          break;
        case MOVE_ROT:
          move_rot(in);
          acknowledge(out);
          break;

      default:
          send_error(out, COULD_NOT_READ);
          break;
      }
    }
  }
  pthread_mutex_unlock(mutex);
}

