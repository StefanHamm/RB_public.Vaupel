#include "nnxt.h"
void Timer(){
    NNXT_LCD_DisplayStringAtLine(0,"Bei Go Druecken bis Stop");
    Delay(1000);
    NNXT_LCD_DisplayStringAtLine(0,"                        ");
    Delay(50);
    NNXT_LCD_DisplayStringAtLine(0,"3");
    Delay(1000);
    NNXT_LCD_DisplayStringAtLine(0,"2");
    Delay(1000);
    NNXT_LCD_DisplayStringAtLine(0,"1");
    Delay(1000);
    NNXT_LCD_DisplayStringAtLine(0,"GO   ");
    Delay(50);
}

int main(){

SensorConfig(Port_0, SensorTouch);
sensor_touch_clicked_t touch;
SensorConfig(Port_0, SensorTouch);
float Timespressed=0;
char Ergebnis[20];
sensor_touch_clicked_t statebefore=SensorTouch_released;

while(true){
  Timer();
    uint32_t starttime=GetSysTime();
    uint32_t endtime=GetSysTime();
    while((starttime+10000)>=endtime){
        Touch_Clicked(Port_0, &touch);
        if((touch==SensorTouch_clicked)&&(statebefore==SensorTouch_released)){
            Timespressed++;
            statebefore=SensorTouch_clicked;

        }else if((touch==SensorTouch_released)&&(statebefore==SensorTouch_clicked)){
        statebefore=SensorTouch_released;
        }
        Delay(10);
        endtime=GetSysTime();
        printf("%ld \n",endtime);
    }
    NNXT_LCD_DisplayStringAtLine(0,"Stop   ");
    Delay(1000);
    NNXT_LCD_DisplayStringAtLine(2,"Ergebnis");
    Timespressed=Timespressed/10;
    sprintf(Ergebnis,"%.2f HZ",Timespressed);
    NNXT_LCD_DisplayStringAtLine(3,Ergebnis);
    Delay (3000);

}
    return 0;
}
