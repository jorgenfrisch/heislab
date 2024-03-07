
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
        setObstruction(&ele);
        stopButtonpressed(&io, &ele);
    }
    freeOrderArray(&io); 
    return 0;
}



