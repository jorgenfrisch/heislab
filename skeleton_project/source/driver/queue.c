
#include "queue.h"

void removeOrder(IO *io, int index){
    
   if(io->size > 0 && index >= 0 && index < io->size && io->orderArray != NULL){
        free(io->orderArray[index]);
        for (int i = index; i < io->size-1; i++){
            io->orderArray[i] = io->orderArray[i+1];
        }
        io->size--;
        io->orderArray = realloc(io->orderArray, io->size*sizeof(order));
    }
}
 


void moveTo(struct elevator *ele, IO *io){
    ele->clock = time(NULL);
    if(io->size > 0){
    int target = io->orderArray[0]->floor;
    if(elevio_floorSensor()!=-1){
    ele->currentFloor = elevio_floorSensor();
    }
    int highest=target;
    int lowest=target;
    for (int i = 0; i<io->size; i++){
        if(ele->currentFloor <= target && io->orderArray[i]->floor >= ele->currentFloor && io->orderArray[i]->floor < target && io->orderArray[i]->button == 0){
            if(io->orderArray[i]->floor < lowest){
                lowest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor >= target && io->orderArray[i]->floor <= ele->currentFloor && io->orderArray[i]->floor > target && io->orderArray[i]->button == 1){
            if(io->orderArray[i]->floor > highest){
                highest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor <= target && io->orderArray[i]->floor >= ele->currentFloor && io->orderArray[i]->floor < target && io->orderArray[i]->button == 2){
            if(io->orderArray[i]->floor < lowest){
                lowest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor >= target && io->orderArray[i]->floor <= ele->currentFloor && io->orderArray[i]->floor > target && io->orderArray[i]->button == 2){
            if(io->orderArray[i]->floor > highest){
                highest=io->orderArray[i]->floor;
            }
        }
        }
    
    if(ele->currentFloor < target){
            target=lowest;
        }
    else if(ele->currentFloor > target){
            target=highest;
        }

    if(elevio_floorSensor()!=-1){ 
    ele->currentFloor = elevio_floorSensor();
    } 
    if (ele->currentFloor < target && ele->doorOpen==0){
        ele->motorDir = DIRN_UP;
        
    } if (ele->currentFloor > target && ele->doorOpen==0){
        ele->motorDir = DIRN_DOWN;
        
    } 

    if (ele->currentFloor == target && ele->doorOpen==0 && elevio_floorSensor()!=-1){
        ele->motorDir = DIRN_STOP;
        doorOpens(ele);
        if(ele->obstruction==1){
            timerStart(ele);
        }

        for(int i = 0; i < io->size; i++){
            if(io->orderArray[i]->floor == target && i<= io->size){
                turnOfButtonLight(io, io->orderArray[i], ele);
                removeOrder(io, i);
                i--;
                printOrderArray(io);
                printf("Target:%d", target);
            }
        } 
        //printf(" dooropen2:%d checktimer : %d ", ele->doorOpen, checkTimer(ele->clock,ele->t) );
    } 
    //printf(" dooropen3 :%d ", ele->doorOpen);
    elevio_motorDirection(ele->motorDir);
    //printf(" %d : %d : %d", ele->clock, ele->t, checkTimer(ele->clock, ele->t));
    }
    if(ele->doorOpen == 1 && checkTimer(ele->clock,ele->t)){
        elevio_doorOpenLamp(0);
        ele->doorOpen=0;
    } else if(ele->doorOpen == 1 && ele->obstruction==1){
        timerStart(ele);
    }
}


