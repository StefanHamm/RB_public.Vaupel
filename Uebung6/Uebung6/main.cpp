#include "nnxt.h"
#include <stdio.h>

//10^-3cm und 10^-3 steigung
const int Kennlinie [8][3]={
{78,80000,-830},//0,4
{102,60000,-384},//0,5
{154,40000,-211},//0,75
{225,25000,-88},//1,1
{338,15000,-37},//1,65
{471,10000,-18},//2,3
{635,7000,-46}, //3,1
{650,0,0}
};

int Auswertung(uint16_t Sensorwert){
    int erg;
for(int i=0;i<7;i++){

    if(Sensorwert<=Kennlinie[i+1][0]){
            erg=Kennlinie[i][1]+(Sensorwert-Kennlinie[i][0])*Kennlinie[i][2]-10000; //-10000 == offset ,kein Korrektur faktor nötig steigung 10^-3 sensorwert nicht verschoben

        return erg<0? 0:erg;
    }
}
}

int main() {
char Ausgabe[20];
uint16_t Sensorwert;
float Entfernung=0;
    while(1) {
SensorADCWithFilter(Port_0,&Sensorwert);
Entfernung = Auswertung(Sensorwert)/1000;
sprintf(Ausgabe,"ENTF: %.2f",Entfernung);
NNXT_LCD_DisplayStringAtLine(0,Ausgabe);
Delay(100);
    }
}
