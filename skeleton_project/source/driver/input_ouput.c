#include "elevator.h"
#include "elevio.h"
#include "input_output.h"
#include "queue.h"

/* void setStop();
void setObstruction();
void setOrderedDirection();
void setOrderedFloor();
void setFloorLight(int floor); */

void initializeIO(struct IO *io){
    io->orders = NULL;
}

void setFloorLights(struct IO *io){
   if(elevio_floorSensor()!=-1 && elevio_floorSensor()!=io->recentFloor){
    io->recentFloor = elevio_floorSensor();
    elevio_floorIndicator(io->recentFloor);
   }
}

void setButtonLights(struct IO *io, struct order *order){
    
}