
#include "nnxt.h"
#include <stdio.h>
#define ReifenUmfang 13.5895  //17.5895
#define DEG_TO_RPM 166.6667
#define KP 5
#define KD 3
#define KI 1




int main(){
char istwerMsg[10];
double sollwert=9; //9cm/s== 0,511668893 umdrehungen fro sekunde
double istwert=0;
double speed=0;
sprintf(istwerMsg,"SW:%.2lf ",sollwert);
NNXT_LCD_DisplayStringAtLine(1,istwerMsg);
uint32_t prev_deg, deg;
uint32_t dt, prev_tick = GetSysTime();
double rps,delta,delta_alt,debug=0,integral=0;
 MotorPortInit(Port_A);
Motor_Tacho_GetCounter(Port_A, &prev_deg);
while(1){

    Delay(500);
    dt = GetSysTime() - prev_tick;
     Motor_Tacho_GetCounter(Port_A, &deg);
     deg = deg - prev_deg;
    rps=(((deg*1.33) * DEG_TO_RPM) / (double)dt)/60;


            istwert=rps*ReifenUmfang;

            delta=sollwert-istwert;
            integral+=(delta*0.5);
            speed = KP*delta+KI*integral+KD*((delta-delta_alt)/0.5);
            if(speed>80)
            speed=80;
            if(speed<0)
                speed=0;
            debug=((delta-delta_alt)/0.5);
            delta_alt=delta;

   printf("Integral:%.2lf,Delta:%.2lf,DReg:%.5lf,RPS:%.3lf\n",integral,delta,debug,rps);

    Motor_Drive(Port_A,Motor_dir_forward,(int)speed);
    printf("speed:%.2lf\n",speed);

    Motor_Tacho_GetCounter(Port_A, &prev_deg);     // Zählerstand für nächste Messung vorbereiten
    prev_tick = GetSysTime();                      // Zeitmessung für nächste Messung vorbereiten
    sprintf(istwerMsg,"IW:%.2lf  ",istwert);
    NNXT_LCD_DisplayStringAtLine(0,istwerMsg);

}


}
