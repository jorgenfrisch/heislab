
#include "elevator.h"

int maxFloor = 3;
int minFloor = 0;

void emergencyStop(void){
       if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
    }
}

void initializeElevator(struct elevator *ele){
    ele->obstruction = 0; //Kan endres
    ele->doorOpen=0;
    elevio_doorOpenLamp(0);
    for(int i = 0; i < N_BUTTONS; i++){
        for(int y = 0; y<N_FLOORS; y++){
            elevio_buttonLamp(y,i,0);
        }
    }
    while(elevio_floorSensor()==-1){
        elevio_motorDirection(DIRN_UP);
        if(elevio_stopButton()){
            emergencyStop();
            break;
        }
    }
    elevio_motorDirection(DIRN_STOP);
    ele->currentFloor=elevio_floorSensor();
}

void timerStart(struct elevator *ele){
    ele->t = time(NULL);
}

int checkTimer(time_t clock, time_t t){
    double time_since_start = difftime(clock, t);
    return (time_since_start >= 3);
}

void doorOpens(struct elevator *ele){
    ele->doorOpen=1;
    timerStart(ele);
    elevio_doorOpenLamp(1);
}

void setObstruction(struct elevator *ele){
    if(ele->doorOpen !=0){
        if(elevio_obstruction()){
            ele->obstruction=1;
        }
        if(!elevio_obstruction()){
            ele->obstruction=0;
        }
    }
}
