
#include "elevator.h"
#include "elevio.h"
#include "input_output.h"


int maxFloor = 3;
int minFloor = 0;

void initializeElevator(struct elevator *elevator, int currentFloor){
    elevator->currentFloor = currentFloor;
}


void moveTo(struct elevator *elevator, int target){
    if (elevator->targetFloor < target){
        elevator->motorDir = DIRN_UP;
        if(elevator->currentFloor == target){
            elevator->motorDir = DIRN_STOP;
        }
    } else if (elevator->targetFloor> target){
        elevator->motorDir = DIRN_DOWN;
        if(elevator->currentFloor == target){
            elevator->motorDir = DIRN_STOP;
        }
    } else {
        elevator->motorDir = DIRN_STOP;
    }
    elevio_motorDirection(elevator->motorDir);
}

void emergencyStop(void){
       if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
    }
}

/* 
void openDoor(...);
void startUp(int timer);
 */
