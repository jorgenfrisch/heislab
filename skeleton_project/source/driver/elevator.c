
#include "elevator.h"
#include "elevio.h"
#include "input_output.h"


int maxFloor = 3;
int minFloor = 0;

void initializeElevator(struct elevator *elevator){
    elevator->currentFloor = elevio_floorSensor();
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
