#include "I2C_DMA.h"
#include "Group_State.h"
#include "dvc_dwt.h"
#include "drv_dwt.h"

#define OLED_ADDRESS 0x78

QueueHandle_t I2C1_DMAQueue;
TaskHandle_t  I2C1_TaskHandle;
SemaphoreHandle_t I2C1_DMA_IDLE;

static Struct_I2C_TransData I2C_TransData;

uint8_t Last_TransNum = 0;                //上一次刷新的数组标志,用于清零
extern uint8_t OLED_DMA_StateFlag;        //看作一个操作句柄

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){

}

uint32_t Last_Refresh_Time = 0;
float FPS = 0.0;
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){                //mem只会进mem的完成回调
  if(hi2c == &hi2c1){
    BaseType_t TaskCall_Flag = 0;

    xSemaphoreGiveFromISR(I2C1_DMA_IDLE, &TaskCall_Flag);         //放出DMA空闲信号量,唤起下一次调度

    Set_Free_BufferBit(&OLED_DMA_StateFlag, Last_TransNum);      //释放这一bit

    FPS = 1.0f / (float)DWT_GetDeltaT(&Last_Refresh_Time);        //
    if(TaskCall_Flag){
      taskYIELD();              //立马发起一次任务调度,保证速度
    }
  }
}

void I2C1_Add_TransData(Struct_I2C_TransData __TransData){
  xQueueSend(I2C1_DMAQueue, &__TransData, 100);
}

//循环调用任务,该任务在任意时间被打断会导致爆栈
void I2C1_DMA_TransTask(){
  while (1)
  {
    xSemaphoreTake(I2C1_DMA_IDLE, portMAX_DELAY);

    xQueueReceive(I2C1_DMAQueue, &I2C_TransData, portMAX_DELAY);

    //HAL_I2C_Master_Transmit_DMA(&hi2c1, OLED_ADDRESS, I2C_TransData.Data, I2C_TransData.Length);

    HAL_I2C_Mem_Write_DMA(&hi2c1, OLED_ADDRESS, 0x40, I2C_MEMADD_SIZE_8BIT, I2C_TransData.Data_Point, I2C_TransData.Length);

    Last_TransNum = I2C_TransData.Num;
  }
}