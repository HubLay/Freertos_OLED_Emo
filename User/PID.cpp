#include "PID.h"

//Mode 1 --- 直立环，以GYRO带入Kd计算。。。。、
//     2 --- 速度环，以正常Kd计算
void Class_PID::Init(float __Kp,float __Ki,float __Kd, int16_t __Out_Max, int16_t __I_Out_Max, int16_t __Out_Min, int16_t __I_Out_Min){
  Kp = __Kp;
  Ki = __Ki;
  Kd = __Kd;

  Out_Max   = __Out_Max;
  I_Out_Max = __I_Out_Max;

  Out_Min   = __Out_Min;
  I_Out_Min = __I_Out_Min;
}

//状态清零
void Class_PID::Reset(){
  Kp_Out = 0;
  Ki_Out = 0;
  Kd_Out = 0;
  Out = 0;
}

void Class_PID::Set_Now(float __Now){
  Now = __Now;
}

void Class_PID::Set_Out(float __Out)
{
  Out = __Out;
}

void Class_PID::Calculate(){
  error = Target - Now;

  Kp_Out = error * Kp;
  Ki_Out += error * Ki;
  Kd_Out = (error-Last_error)*Kd;

  Last_error = error;
  if(Ki_Out > I_Out_Max){
    Ki_Out = I_Out_Max;
  }
  else if(Ki_Out < I_Out_Min){
    Ki_Out = I_Out_Min;
  }

  Out = Kp_Out + Ki_Out + Kd_Out;

  if(Out > Out_Max){
    Out = Out_Max;
  }
  else if(Out < Out_Min){
    Out = Out_Min;
  }
}

void Class_PID::Set_Target(float __Target){
  Target = __Target;
}

float Class_PID::Get_Out(){
  return Out;
}