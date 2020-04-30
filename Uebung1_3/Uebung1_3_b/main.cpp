#include "nnxt.h"
void detektiereObjekt(uint8_t *dist){


    sensor_error_t err;

    char distStr[20];
    again:
    err = US_GetDistance(Port_0,dist);
    if (err!=sensor_error_NoError){
        NNXT_LCD_DisplayStringAtLine(0, "Sensor Error!!!!   ");
        Delay(20);
        goto again;
    }
    sprintf(distStr,"Entfernung:%u    ",*dist);
        NNXT_LCD_DisplayStringAtLine(0,distStr);
        Delay(50);



}

int main(){

Delay(50);
SensorConfig(Port_0, SensorUS);
MotorPortInit(Port_A);
MotorPortInit(Port_B);
uint8_t abstand=0;

while(1){
detektiereObjekt(&abstand);
        while(abstand>30){
                detektiereObjekt(&abstand);
                Motor_Drive(Port_A,Motor_dir_forward,100);
                Motor_Drive(Port_B,Motor_dir_forward,100);
                Delay(20);
    }
        while(abstand<30){
                detektiereObjekt(&abstand);
                Motor_Drive(Port_A,Motor_dir_backward,50);
                Motor_Drive(Port_B,Motor_dir_forward,50);
                Delay(20);


        }

        Delay(20);


}
    return 0;
}
