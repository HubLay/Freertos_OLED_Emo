#include "Group_State.h"


//寻找空闲数组    bit ------ 1-8
uint8_t Find_Free_Buffer(uint8_t __StateFlag, uint8_t Buffer_Num){
  for(int i = 1; i <= Buffer_Num; i++){
    if(!(__StateFlag & (1 << (i-1) ))){
      return i;
    }
  }
  return 0;          //找不到返回0
}

//将某个bit设置为占用
void Set_Busy_BufferBit(uint8_t *__StateFlag, uint8_t Bit){
  if(Bit <= 0 || Bit > 8){
    return;
  }

  *__StateFlag = *__StateFlag | (1 << (Bit - 1));
}

//将某个bit设置为空闲
void Set_Free_BufferBit(uint8_t *__StateFlag, uint8_t Bit){
  if(Bit <= 0 || Bit > 8){
    return;
  }

  *__StateFlag = *__StateFlag & (~(1 << (Bit-1)));
}