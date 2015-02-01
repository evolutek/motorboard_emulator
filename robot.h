#ifndef _ROBOT_H
#define _ROBOT_H

#include <stdio.h>

typedef struct{
  float xpos;
  float ypos;
  float theta;
  float vdep;
  float omega;
  float vG, vD;
  float diamG, diamD;
  float distroues;
  float olddist;
  float oldth;
  float indexG;
  float indexD;
  float wpX;
  float wpY;
  float wpTheta;
  float futur_x;
  float futur_y;
  float trp,tri,trd;
  float rtp,rti,rtd;
  int moving;
  int recalage;
} t_robot;

typedef struct{
  float trsl_acc;
  float trsl_dec;
  float trsl_max;
  float rot_acc;
  float rot_dec;
  float rot_max;
  int free;
  float time;
  int telemetry;
  int debug;
  float last_send;
  float delta_trsl_max;
  float delta_rot_max;
} s_default;


#endif
