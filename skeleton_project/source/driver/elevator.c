
#include "elevator.h"
#include "elevio.h"
#include "input_output.h"


int maxFloor = 3;
int minFloor = 0;

void emergencyStop(void){
       if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
    }
}

void initializeElevator(struct elevator *elevator){
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
    elevator->currentFloor=elevio_floorSensor();
}


void moveTo(struct elevator *elevator, int target){
    if(elevio_floorSensor()!=-1){
    elevator->currentFloor = elevio_floorSensor();
    }
    if (elevator->currentFloor < target){
        elevator->motorDir = DIRN_UP;
    } else if (elevator->currentFloor > target){
        elevator->motorDir = DIRN_DOWN;
    } else if (elevator->currentFloor == target){
        elevator->motorDir = DIRN_STOP;
    } 
    elevio_motorDirection(elevator->motorDir);
    emergencyStop();
}


/* 
void openDoor(...);
void startUp(int timer);
 */
