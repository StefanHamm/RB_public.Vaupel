#include "nnxt.h"


int main(){
MotorPortInit(Port_A);
MotorPortInit(Port_B);
int spirale=1;

while(true){


    Motor_Drive(Port_A,Motor_dir_forward,100); //Drive forward
    Motor_Drive(Port_B,Motor_dir_forward,100);
    Delay(1000*((float)spirale/4));
    Motor_Stop(Port_A,Motor_stop_float);
    Motor_Stop(Port_B,Motor_stop_float);
    Delay(100);

    Motor_Drive(Port_A,Motor_dir_forward,50); //turn 90
    Motor_Drive(Port_B,Motor_dir_backward,50);
    Delay(725);
    Motor_Stop(Port_A,Motor_stop_float);
    Motor_Stop(Port_B,Motor_stop_float);
    Delay(1000);
    spirale++;

}
    return 0;
}
