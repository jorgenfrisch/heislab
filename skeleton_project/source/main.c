
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/input_output.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    struct elevator ele;
    initializeElevator(&ele);
    IO io;
    initializeIO(&io);
    while(1){

        setFloorLights(&io);
        setOrders(&io, &ele);
        moveTo(&ele, &io);
    
        // if(elevio_stopButton()){
        //     elevio_motorDirection(DIRN_STOP);
        //      break;
        // }
        stopButtonpressed(&io, &ele);
    }
    printOrderArray(&io);
    freeOrderArray(&io); 
    return 0;
}



