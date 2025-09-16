#ifndef __MYEMO_H
#define __MYEMO_H

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "oled.h"
#include "PID.h"

class Class_Eye{

public:
  Class_PID Lenght_PID;

  int8_t Width;
  float Lenght;
  int16_t Eyes_X;
  int16_t Eyes_Y; 
  int16_t Eyes_R;

  uint8_t Close_Complete_Flag;            //完成一次闭眼操作
};

class Class_EmoEyes{

public:
  void Init(uint8_t __Eyes_Size = 20, uint8_t __Eyes_Interval_Base = 6);

  void Blink(class Class_Eye *__Eye);

  void Emo_Updata();

private:
  uint32_t Last_Refresh_Time;
  float FPS;

  uint8_t Eyes_Size;                //眼睛基础大小
  uint8_t Eyes_Interval_Base;       //双眼基本间隔
  uint8_t Eyes_Interval_Set;        //双眼设置的间隔

  Class_Eye Left_Eye;
  Class_Eye Rigth_Eye;

  uint8_t Blink_Flag;       //眨眼标志位

  void Eyes_Show(class Class_Eye __Eye);
};

#ifdef __cplusplus
}
#endif


#endif