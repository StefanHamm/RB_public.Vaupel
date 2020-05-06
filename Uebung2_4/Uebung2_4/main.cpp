#include "nnxt.h"
volatile uint8_t Rclick=0;
volatile uint8_t Lclick=0;
void rechtsstask(){
    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_0, &touch);

        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
              Rclick=1;
            }

        statebefore=SensorTouch_released;

        Delay(100);
}

    }

void linksstask(){
    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_1, &touch);
        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
            Lclick=1;
        }
        statebefore=SensorTouch_released;

        Delay(100);

    }


}
void Task3(){
    motor_dir_t Richtung=Motor_dir_forward;


while(1){
      if(Rclick){
        switch(Richtung){
    case Motor_dir_forward:Richtung=Motor_dir_backward;NNXT_LCD_DisplayStringAtLine(0,"Rückwärts ");break;
    case Motor_dir_backward:Richtung=Motor_dir_forward;NNXT_LCD_DisplayStringAtLine(0,"Vorwärts ");break;
    default:break;
        }
        Rclick=0;
      }

    if(Lclick==1){

        Motor_Drive(Port_A,Richtung,35);
        Motor_Drive(Port_B,Richtung,35);
        Delay(1000);
        Motor_Stop(Port_A,Motor_stop_break);
        Motor_Stop(Port_B,Motor_stop_break);
        Lclick=0;
    }


}
}
int main(){
    NNXT_LCD_DisplayStringAtLine(0,"Vorwärts ");
    SensorConfig(Port_0,SensorTouch);
    SensorConfig(Port_1,SensorTouch);
    MotorPortInit(Port_A);
    MotorPortInit(Port_B);
CreateAndStartTask(rechtsstask);
CreateAndStartTask(linksstask);
CreateAndStartTask(Task3);

StartScheduler();

    return 0;
}
