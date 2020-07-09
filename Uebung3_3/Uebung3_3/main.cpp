#include "nnxt.h"
#include <stdio.h>
#include "Event.h"

#define Rclick_ev 0            //mit define events festlegen zischen 0 und 15
#define Lclick_ev 1
#define Lock 2
#define Timer_10s_ev 3
#define Timer_15s_ev 4
#define Home_ev 5

#define STATE_START 0
#define STATE_TURN_L 1
#define STATE_TURN_R 2
#define STATE_DRIVE 3
#define STATE_POS 4
#define STATE_TURN_UP 5

enum Ausrichtung{ausr_links=-90,ausr_oben=0,ausr_rechts=90};


void rechtsstask(){

    sensor_touch_clicked_t touch =SensorTouch_released,statebefore=SensorTouch_released;

while(true){

        Touch_Clicked(Port_0, &touch);

        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            statebefore=SensorTouch_clicked;
              setEvent(Rclick_ev);
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
            setEvent(Lclick_ev);
        }
        statebefore=touch;

        Delay(100);

    }


}
void Turn(Ausrichtung Richtung){
if(Richtung==ausr_links){
    Motor_Drive(Port_B,Motor_dir_forward,50); //turn 90
    Motor_Drive(Port_A,Motor_dir_backward,50);
    Delay(718);
    Motor_Stop(Port_A,Motor_stop_float);
    Motor_Stop(Port_B,Motor_stop_float);

    return;
}else{
 Motor_Drive(Port_A,Motor_dir_forward,50); //turn 90 Rechts
    Motor_Drive(Port_B,Motor_dir_backward,50);
    Delay(718);
    Motor_Stop(Port_A,Motor_stop_float);
    Motor_Stop(Port_B,Motor_stop_float);

return;
}

}



void Automat(){
    uint8_t State=STATE_START;
    int Richtung = 0,Pos=0;;
char Ausgabe1[20],Ausgabe2[20],Ausgabe3[20];
sprintf(Ausgabe3,"Zeit vorbei Home");

while(true){
    switch(State){
    case STATE_START:
        NNXT_LCD_DisplayStringAtLine(1,"                    ");
        if(eventIsSet(Lclick_ev)){
            clearEvent(Lclick_ev);
            State=STATE_TURN_L;
        }
        else if(eventIsSet(Rclick_ev)){
            clearEvent(Rclick_ev);
            State=STATE_TURN_R;
        }
        break;

    case STATE_TURN_L:
        if(Richtung==ausr_links){
            Motor_Drive(Port_A,Motor_dir_forward,35);
            Motor_Drive(Port_B,Motor_dir_forward,35);
            startTimer(Timer_10s);
            Pos--;
            State=STATE_DRIVE;
        }
        else {
            Turn(ausr_links);
            Richtung-=90;
        }
break;
    case STATE_TURN_R:
         if(Richtung==ausr_rechts){
            Motor_Drive(Port_A,Motor_dir_forward,35);
            Motor_Drive(Port_B,Motor_dir_forward,35);
            startTimer(Timer_10s);
            Pos++;
            State=STATE_DRIVE;
        }
        else {
            Turn(ausr_rechts);
            Richtung+=90;
        }
break;
    case STATE_DRIVE:
        if(eventIsSet(Timer_10s_ev)){
            clearEvent(Timer_10s_ev);
            clearEvent(Lclick_ev);
            clearEvent(Rclick_ev);
            Motor_Stop(Port_A,Motor_stop_break);
            Motor_Stop(Port_B,Motor_stop_break);
            startTimer(Timer_15s);
            State=STATE_POS;
        }
        break;
    case STATE_POS:
        if(eventIsSet(Timer_15s_ev)){
            clearEvent(Timer_15s_ev);
            setEvent(Home_ev);
        }
        else if(eventIsSet(Home_ev)&&(Pos==0)){
           clearEvent(Home_ev);
           State=STATE_TURN_UP;
           }
           else if(eventIsSet(Home_ev)&&(Pos<0)){
            cancleTimer(Timer_15s);
            State=STATE_TURN_R;
           }
           else if(eventIsSet(Home_ev)&&(Pos>0)){
            cancleTimer(Timer_15s);

            State=STATE_TURN_L;
           }
        else if((eventIsSet(Lclick_ev))&&(Pos>-3)){
            cancleTimer(Timer_15s);

            State=STATE_TURN_L;
        }
         else if((eventIsSet(Rclick_ev))&&(Pos<3)){
            cancleTimer(Timer_15s);
            State=STATE_TURN_R;
        }
        break;




    case STATE_TURN_UP:

        if(Richtung==ausr_oben){
            State=STATE_START;

        }
        if(Richtung==ausr_rechts){
            Turn(ausr_links);
        Richtung-=90;
        }
        if(Richtung==ausr_links){
            Turn(ausr_rechts);
            Richtung+=90;
        }
    break;
        default:break;
    }
sprintf(Ausgabe1,"Pos:%d  ",Pos);
NNXT_LCD_DisplayStringAtLine(0,Ausgabe1);

if(eventIsSet(Home_ev))
NNXT_LCD_DisplayStringAtLine(1,Ausgabe3);
Delay(100);
}
}

int main(){
     MotorPortInit(Port_A);
    MotorPortInit(Port_B);
    Turn(ausr_rechts);
    Delay(100);
    Turn(ausr_rechts);
    SensorConfig(Port_0,SensorTouch);
    SensorConfig(Port_1,SensorTouch);
setTimer(Timer_10s,1500,Timer_10s_ev);
setTimer(Timer_15s,5000,Timer_15s_ev);
CreateAndStartTask(TimerTask);
CreateAndStartTask(rechtsstask);
CreateAndStartTask(linksstask);
CreateAndStartTask(Automat);

StartScheduler();





    return 0;
    }
