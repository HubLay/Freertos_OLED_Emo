#include "MyTask.h"
#include "stdio.h"
#include "MyEmo.h"
#include "drv_dwt.h"

Class_EmoEyes EmoEyes;
TimerHandle_t Timer1;

// int Count = 0;
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
  
//   if (htim == &htim2)
//   {
//   //  char Mes[20] = "Hello";
//   //  sprintf(Mes, "Count: %d", Count);
//   //  OLED_PrintASCIIString(15, 0, Mes, &afont12x6, OLED_COLOR_NORMAL);
//   //  OLED_DrawLine(0, 12, 128, 12, OLED_COLOR_NORMAL);
//   //  OLED_ShowFrame();
//     //Updata_Point();
    
//   }
// }

void Task_Init(){
  DWT_Init(84);

  OLED_Init();
  OLED_SetColorMode(OLED_COLOR_NORMAL);

  OLED_DisPlay_On();
  OLED_NewFrame();
	
  EmoEyes.Init(30, 10);
}

void Updata_Point()
{ 

}

void MyTimerCallback(TimerHandle_t xTimer){
  if(xTimer == Timer1){
    static uint8_t Init_Flag = 0;
    if(!Init_Flag){
      Task_Init();
      Init_Flag = 1;
    }

    EmoEyes.Emo_Updata();

  }
}


