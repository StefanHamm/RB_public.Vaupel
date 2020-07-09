#include "nnxt.h"
#include <stdio.h>
#include "Event.h"
#define Rclick 0            //mit define events festlegen zischen 0 und 15
#define Lclick 1
#define Lock 2
#define Timer_10s_ev 3
#define Timer_15s_ev 4
void rechtsstask(){

    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_0, &touch);

        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
              setEvent(Rclick);
            }

        statebefore=touch;

        Delay(100);
}

    }

void linksstask(){
    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_1, &touch);
        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
            setEvent(Lclick);
        }
        statebefore=touch;

        Delay(100);

    }


}




void Task3(){
    motor_dir_t Richtung=Motor_dir_forward;


while(1){
      if(eventIsSet(Rclick)){
        switch(Richtung){
    case Motor_dir_forward:Richtung=Motor_dir_backward;NNXT_LCD_DisplayStringAtLine(0,"Rückwärts ");break;
    case Motor_dir_backward:Richtung=Motor_dir_forward;NNXT_LCD_DisplayStringAtLine(0,"Vorwärts ");break;
    default:break;
        }
        clearEvent(Rclick);
      }

    if(eventIsSet(Lclick)&&(!eventIsSet(Lock))){
        clearEvent(Lclick);
        taskENTER_CRITICAL();
        Motor_Drive(Port_A,Richtung,35);
        Motor_Drive(Port_B,Richtung,35);
        taskEXIT_CRITICAL();
        startTimer(Timer_10s);
        setEvent(Lock);        //damit nicht während dem fahren die richtung gewechselt werden kann

    }
if (eventIsSet(Timer_10s_ev)){
    clearEvent(Timer_10s_ev);
    clearEvent(Lock);
    clearEvent(Lclick);
    taskENTER_CRITICAL();
    Motor_Stop(Port_A,Motor_stop_break);
    Motor_Stop(Port_B,Motor_stop_break);
    taskEXIT_CRITICAL();

}
Delay(50);
}
}

int main(){
    SensorConfig(Port_0,SensorTouch);
    SensorConfig(Port_1,SensorTouch);
setTimer(Timer_10s,3000,Timer_10s_ev);
setTimer(Timer_15s,9000,Timer_15s_ev);
CreateAndStartTask(TimerTask);
CreateAndStartTask(rechtsstask);
CreateAndStartTask(linksstask);
CreateAndStartTask(Task3);

StartScheduler();





    return 0;
    }
