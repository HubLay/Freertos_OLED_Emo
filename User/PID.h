#ifndef __PID_H
#define __PID_H
#include <stdint.h>

class Class_PID{
public:
  void Init(float __Kp,float __Ki,float __Kd, int16_t __Out_Max, int16_t __I_Out_Max, int16_t __Out_Min, int16_t __I_Out_Min);

  float Get_Out();
  
  void Set_Now(float __Now);
  void Set_Out(float __Out);
  void Set_Target(float __Target);

  void Reset();

  virtual void Calculate();
private:
  float Now, Target;
  float error, Last_error;
  float Kp,Ki,Kd;
  float Out, Kp_Out, Ki_Out, Kd_Out;

  int16_t Out_Max;
  int16_t Out_Min;
  int16_t I_Out_Max;
  int16_t I_Out_Min;
};


#endif