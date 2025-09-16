#include "MyEmo.h"
#include "dvc_dwt.h"
#include "stdio.h"
#include "math.h"

#include "FreeRTOS.h"
#include "task.h"

#define Eyes_Radius 6

#define OLED_Clear_GRAM OLED_NewFrame        //清空OLED显存
//#define OLED_Refresh_GRAM OLED_ShowFrame     //将GRAM写入OLED
#define OLED_Refresh_GRAM OLED_ShowFrame_DMA     //将GRAM写入OLED DMA方式
#define OLED_Draw_Eyes(x, y,  w, h, r)  OLED_DrawFilledRoundRect((uint8_t)x, (uint8_t)y, (uint8_t)w, (uint8_t)h, (uint8_t)r,OLED_COLOR_NORMAL)

void Class_EmoEyes::Init(uint8_t __Eyes_Size, uint8_t __Eyes_Interval_Base){
  Eyes_Size = __Eyes_Size;
  Eyes_Interval_Base = __Eyes_Interval_Base;
  Eyes_Interval_Set  = Eyes_Interval_Base;

  // Left_Eye.Lenght_PID.Init(0, 0.00005, 0, 20, 20, -20, -20);
  // Rigth_Eye.Lenght_PID.Init(0, 0.00005, 0, 20, 20, -20, -20);

  Left_Eye.Lenght_PID.Init(0.0, 0.00001, 0, 20, 20, -20, -20);
  Rigth_Eye.Lenght_PID.Init(0.0, 0.00001, 0, 20, 20, -20, -20);

  Left_Eye.Eyes_R = Eyes_Radius;
  Rigth_Eye.Eyes_R = Eyes_Radius;

  Left_Eye.Lenght = Eyes_Size;
  Left_Eye.Width = Eyes_Size;
  Rigth_Eye.Lenght = Eyes_Size;
  Rigth_Eye.Width = Eyes_Size;

  OLED_Clear_GRAM();
}

//PID跑的眼睛眨动,更加灵活
void Class_EmoEyes::Blink(class Class_Eye *__Eye)
{
  if (!__Eye->Close_Complete_Flag)
  {
    __Eye->Lenght_PID.Set_Now(__Eye->Lenght);
    __Eye->Lenght_PID.Set_Target(2);
    __Eye->Lenght_PID.Calculate();
  }
  else
  {
    __Eye->Lenght_PID.Set_Now(__Eye->Lenght);
    __Eye->Lenght_PID.Set_Target(Eyes_Size);
    __Eye->Lenght_PID.Calculate();
  }

  __Eye->Lenght += __Eye->Lenght_PID.Get_Out();
  // if (__Eye->Lenght <= 2.0f && !__Eye->Close_Complete_Flag)
  // {
  //   __Eye->Close_Complete_Flag = 1;
  // }
  // if (__Eye->Lenght >= Eyes_Size && __Eye->Close_Complete_Flag)
  // {
  //   __Eye->Close_Complete_Flag = 0;
  // }
  if (__Eye->Lenght <= 2.0f)
  {
    __Eye->Lenght = 2.0f;
    __Eye->Close_Complete_Flag = 1;
  }
  if (__Eye->Lenght >= Eyes_Size)
  {
    __Eye->Lenght = Eyes_Size;
    __Eye->Close_Complete_Flag = 0;
  }

}

void Class_EmoEyes::Eyes_Show(const class Class_Eye __Eye)
{
  OLED_Draw_Eyes(__Eye.Eyes_X, __Eye.Eyes_Y, __Eye.Width, __Eye.Lenght, __Eye.Eyes_R);
}

char Mes[20];
uint16_t Count = 0;
void Class_EmoEyes::Emo_Updata()
{
  OLED_Clear_GRAM();
  //坐标系以屏幕左上角为原点，向下为Y，右为X
  Blink_Flag = 1;

  if(Blink_Flag){         //眨眼效果
    Blink(&Left_Eye);
    Blink(&Rigth_Eye);
  }
  else{
    Left_Eye.Lenght = Eyes_Size;
    Rigth_Eye.Lenght = Eyes_Size;
  }

  Left_Eye.Eyes_X = OLED_COLUMN / 2 - (Eyes_Interval_Set / 2 + Left_Eye.Width);      //x从屏幕中线开始计算
  Left_Eye.Eyes_Y = OLED_ROW   / 2 - (Left_Eye.Lenght / 2);

  Rigth_Eye.Eyes_X = OLED_COLUMN / 2 + (Eyes_Interval_Set / 2);
  Rigth_Eye.Eyes_Y = OLED_ROW   / 2 - (Rigth_Eye.Lenght / 2);

  Eyes_Show(Left_Eye);
  Eyes_Show(Rigth_Eye);

  // Count ++;

  // sprintf(Mes, "Count: %d", Count);
  // OLED_PrintString(10, 10, Mes, &font16x16, OLED_COLOR_NORMAL);

  OLED_Refresh_GRAM();
}
