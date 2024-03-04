
#include "queue.h"



// void runEle(IO *io, struct elevator *ele){
//     if (io->size > 0){
//         for (int i = 0; i < io->size; i++){
//             while(ele->currentFloor != io->orderArray[i]->floor){
//             int f = io->orderArray[i]->floor;
//             moveTo(&ele, f);
//             }
//         }
//     }
// }


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
        if(ele->currentFloor < target && io->orderArray[i]->floor < ele->currentFloor && io->orderArray[i]->floor < target && io->orderArray[i]->button == 0){
            if(io->orderArray[i]->floor < lowest){
                lowest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor > target && io->orderArray[i]->floor > ele->currentFloor && io->orderArray[i]->floor > target && io->orderArray[i]->button == 1){
            if(io->orderArray[i]->floor > highest){
                highest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor < target && io->orderArray[i]->floor < target && io->orderArray[i]->floor < ele->currentFloor && io->orderArray[i]->button == 2){
            if(io->orderArray[i]->floor < lowest){
                lowest=io->orderArray[i]->floor;
            }
        }
        else if(ele->currentFloor > target && io->orderArray[i]->floor > ele->currentFloor && io->orderArray[i]->floor > target && io->orderArray[i]->button == 2){
            if(io->orderArray[i]->floor > highest){
                highest=io->orderArray[i]->floor;
            }
        }
        }
        if(ele->currentFloor < target){
            target=lowest;
        }
        if(ele->currentFloor > target){
            target=highest;
        }
        printf("%d", ele->currentFloor);
    printf("%d", target);

    if (ele->currentFloor < target){
        ele->motorDir = DIRN_UP;
    } else if (ele->currentFloor > target){
        ele->motorDir = DIRN_DOWN;
    } else if (ele->currentFloor == target){
        ele->motorDir = DIRN_STOP;
    } 
    
    elevio_motorDirection(ele->motorDir);
    }
    emergencyStop();
}