#ifndef __MYTASK_H_
#define __MYTASK_H_

#include "tim.h"
#include <stdio.h>
#include <stdlib.h>
#include "oled.h"
#include "font.h"
#include "i2c.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#include "task.h"

#ifdef __cplusplus
extern "C"{
#endif

void MyTimerCallback(TimerHandle_t xTimer);

void Task_Init();

#ifdef __cplusplus
}
#endif

#endif