#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
volatile uint16_t GlobalEventmanager=0;


typedef struct Timer_s{
    int IsStarted=0;
    int time=0;
    uint32_t starttime=0;
    uint32_t endtime=0;
    int Event;
}TimerType;
volatile TimerType Timer_10s,Timer_15s;


void setEvent(int ev){
    taskENTER_CRITICAL();
uint16_t mask=0x01;
mask =  mask<<ev;
GlobalEventmanager = GlobalEventmanager|mask;
taskEXIT_CRITICAL();
}

bool eventIsSet(int ev){
uint16_t mask=0x01;
uint16_t GlobalEvcopy=GlobalEventmanager;
mask=mask<<ev;
GlobalEvcopy=GlobalEvcopy&mask;
if(GlobalEvcopy)
    return true;
else
    return false;
}

void clearEvent(int ev){
    taskENTER_CRITICAL();
uint16_t mask=0x01;
mask=mask<<ev;
mask=~mask;
GlobalEventmanager=GlobalEventmanager&mask;
taskEXIT_CRITICAL();
}

void setTimer(volatile TimerType &timer,int time,int ev ){
timer.time=time;
timer.Event=ev;
return;
}

void startTimer(volatile TimerType &timer){
    if(!timer.IsStarted){
    taskENTER_CRITICAL();
    timer.starttime=GetSysTime();
    timer.endtime=timer.starttime+timer.time;
    timer.IsStarted=1;
    taskEXIT_CRITICAL();
    }

    return;
}

void cancleTimer(volatile TimerType &timer){
timer.IsStarted=0;
return;
}

bool isTimerStarted(volatile TimerType &timer){
if (timer.IsStarted){
    return true;
}
return false;
}


bool runtimer(volatile TimerType &timer){

if (timer.IsStarted==0)
    return false;
if(timer.endtime<=timer.starttime){
timer.IsStarted=0;
return true;
}
else{

    timer.starttime=GetSysTime();
return false;
}
}

void TimerTask(){


while(true){
if(isTimerStarted(Timer_10s)){
    if(runtimer(Timer_10s))
        setEvent(Timer_10s.Event);
}

if(isTimerStarted(Timer_15s)){
    if(runtimer(Timer_15s))
        setEvent(Timer_15s.Event);
}

Delay(50);

}
}


#endif // EVENT_H_INCLUDED
