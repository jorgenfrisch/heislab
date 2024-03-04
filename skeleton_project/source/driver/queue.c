
#include "queue.h"


void removeOrder(IO *io, int index){
    if(io->size > 0 && index >= 0 && index < io->size){
        for (int i = index; i < io->size-1; i++){
            io->orderArray[i] = io->orderArray[i+1];
        }
        free(io->orderArray[io->size-1]);
        io->size--;
        io->orderArray = realloc(io->orderArray, io->size*sizeof(order));
    }
} 



void moveTo(struct elevator *ele, IO *io){
    // if (io->size == 0 || elevator->currentFloor == io->orderArray[0]->floor) {
    //     elevator->motorDir = DIRN_STOP;
    //     return;
    // }
    if(io->size >0){
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
    //printf(" %d%d%d ", target, lowest, ele->currentFloor);
    if(elevio_floorSensor()!=-1){ 
    ele->currentFloor = elevio_floorSensor();
    } 
    if (ele->currentFloor < target){
        ele->motorDir = DIRN_UP;
    } if (ele->currentFloor > target){
        ele->motorDir = DIRN_DOWN;
    } if (ele->currentFloor == target){
        ele->motorDir = DIRN_STOP;


        for(int i = 0; i < io->size; i++){
            if(io->orderArray[i]->floor == target && i<=io->size){
                turnOfButtonLight(io, io->orderArray[i], ele);
                removeOrder(io, i);
            }
        } 
    } 
    elevio_motorDirection(ele->motorDir);
    printf(" %d%d%d ", target, lowest, ele->currentFloor);
    }
    emergencyStop();
}

/*  int a = 1; 
    while(a == 1){
        int changes = 0;
        for(int i = 0; i < io->size; i++){
        
            if(io->orderArray[i]->floor == target){
            turnOfButtonLight(io, io->orderArray[i], ele);
            removeOrder(io, i);
            changes++;
            break; 
        }
        
    }
    if(changes == 0){
        a = 0; 
    }
}
 */
