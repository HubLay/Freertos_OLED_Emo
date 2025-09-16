#ifndef __GROUP_STATE_H
#define __GROUP_STATE_H

#include "stdint.h"

uint8_t Find_Free_Buffer(uint8_t __StateFlag, uint8_t Buffer_Num);
void Set_Busy_BufferBit(uint8_t *__StateFlag, uint8_t Bit);
void Set_Free_BufferBit(uint8_t *__StateFlag, uint8_t Bit);


#endif