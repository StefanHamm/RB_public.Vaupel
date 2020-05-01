#include "nnxt.h"
volatile motor_dir_t Richtung = Motor_dir_forward;
volatile uint8_t Drive=0;
void rechtsstask(){
    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_0, &touch);
        char Ausgabe[20];
        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
            if(Drive==0)
            switch (Richtung){
            case Motor_dir_forward:Richtung=Motor_dir_backward;NNXT_LCD_DisplayStringAtLine(0,"Rückwärts");break;
            case Motor_dir_backward:Richtung=Motor_dir_forward;NNXT_LCD_DisplayStringAtLine(0,"Vorwärts ");break;
            default:break;
            }


        }else if((touch==SensorTouch_released)&&(statebefore==SensorTouch_clicked)){
        statebefore=SensorTouch_released;
        }
        Delay(100);

    }


}
void linksstask(){
    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_1, &touch);
        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
            if(Drive==0)
                Drive++;
        }else if((touch==SensorTouch_released)&&(statebefore==SensorTouch_clicked)){
        statebefore=SensorTouch_released;
        }
        Delay(100);

    }


}
void Task3(){
while(1){
    if(Drive==1){
        taskENTER_CRITICAL();
        Motor_Drive(Port_A,Richtung,35);
        Motor_Drive(Port_B,Richtung,35);
        Delay(1000);
        Motor_Stop(Port_A,Motor_stop_break);
        Motor_Stop(Port_B,Motor_stop_break);
        Drive=0;
        taskEXIT_CRITICAL();

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
