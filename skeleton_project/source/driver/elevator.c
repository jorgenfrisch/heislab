
#include "elevator.h"

int maxFloor = 3;
int minFloor = 0;

void emergencyStop(void){
       if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
    }
}

void initializeElevator(struct elevator *ele){
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

void doorOpens(struct elevator *ele){
    struct timespec delay;
    delay.tv_sec = 3;
    delay.tv_nsec = 0;
    elevio_doorOpenLamp(1);
    ele->doorOpen=1;
    ele->motorDir = DIRN_STOP;
    elevio_motorDirection(ele->motorDir);
   /*  while(1){
        if(ele->obstruction==0){
            break;
        }
    } */
    nanosleep(&delay,NULL);
    ele->doorOpen=0;
    elevio_doorOpenLamp(0);
}

void setObstruction(struct elevator *ele){
    if(ele->doorOpen !=0){
        if(elevio_obstruction()){
            ele->obstruction=1;
        }
    }
}
