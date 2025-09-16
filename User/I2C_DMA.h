#ifndef __OELD_DMA_H
#define __OELD_DMA_H

#include "main.h"
#include "i2c.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

typedef struct{
  uint16_t Length;
  uint8_t Num;
  uint8_t *Data_Point;
}Struct_I2C_TransData;

extern QueueHandle_t I2C1_DMAQueue;

void I2C1_DMA_TransTask();
void I2C1_Add_TransData(Struct_I2C_TransData __TransData);


#endif