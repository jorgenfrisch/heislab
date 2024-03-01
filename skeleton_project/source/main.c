#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/elevator.h"
#include "driver/input_output.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);
    struct elevator ele;
    initializeElevator(&ele);
    struct IO io;
    initializeIO(&io);
    while(1){
       setFloorLights(&io);
        setOrders(&io, &ele);
       if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
             break;
        }
        //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    printOrderArray(&io);
    freeOrderArray(&io);
    return 0;
}
