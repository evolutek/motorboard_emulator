#ifndef _COMMAND_H
#define _COMMAND_H

#include <stdio.h>
#include <stdint.h>
#include "queue.h"

typedef enum{
  DEBUG_MESSAGE      = 127,
  DEBUG              = 126,
  ACKNOWLEDGE        = 200,
  MOVE_BEGIN         = 128,
  MOVE_END           = 129,
  GET_PID_TRSL       = 10,
  GET_PID_ROT        = 11,
  GET_POSITION       = 12,
  GET_SPEEDS         = 13,
  GET_WHEELS         = 14,
  GET_DELTA_MAX      = 15,
  GET_VECTOR_TRSL    = 16,
  GET_VECTOR_ROT     = 17,
  GOTO_XY            = 100,
  GOTO_THETA         = 101,
  MOVE_TRSL          = 102,
  MOVE_ROT           = 103,
  CURVE              = 104,
  FREE               = 109,
  RECALAGE           = 110,
  SET_PWM            = 111,
  STOP_ASAP          = 112,
  SET_PID_TRSL       = 150,
  SET_PID_ROT        = 151,
  SET_TRSL_ACC       = 152,
  SET_TRSL_DEC       = 153,
  SET_TRSL_MAXSPEED  = 154,
  SET_ROT_ACC        = 155,
  SET_ROT_DEC        = 156,
  SET_ROT_MAXSPEED   = 157,
  SET_X              = 158,
  SET_Y              = 159,
  SET_THETA          = 160,
  SET_DIAM_WHEELS    = 161,
  SET_WHEELS_SPACING = 162,
  SET_DELTA_MAX_ROT  = 163,
  SET_DELTA_MAX_TRSL = 164,
  SET_DEBUG          = 200,
  SET_TELEMETRY      = 201,
  INIT               = 254,
  ERROR              = 255
} t_command;

typedef struct{
  int x;
  int y;
  int theta;
} t_robot;

void dispatcher(Queue* q);

#endif

