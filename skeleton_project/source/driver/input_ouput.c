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
    io->size = 0;
    io->orderArray = NULL;
    io->orderArray = (struct order*)malloc(io->size*sizeof(struct order));


}

void setStop(struct IO *io){
    io->stop = elevio_stopButton();
}

void setObstruction(struct IO *io){
    io->obstruction = elevio_obstruction();
}

void setFloorLights(struct IO *io){
   if(elevio_floorSensor()!=-1 && elevio_floorSensor()!=io->recentFloor){
    io->recentFloor = elevio_floorSensor();
    elevio_floorIndicator(io->recentFloor);
   }
}

void setButtonLights(struct IO *io, struct order *order, struct elevator *ele){

    elevio_buttonLamp(order->floor, order->button, 1);

    if (order->floor == ele->targetFloor){
        elevio_buttonLamp(order->floor, order->button, 0);
    }
}

struct order* buttonCallback(){
        for(int f = 0; f < N_FLOORS; f++){
             for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1){
                    struct order *buttonOrder;
                    buttonOrder->floor = f;
                    buttonOrder->button = b;
                    return buttonOrder;
                }
        }
    } 
}

void setOrders(struct IO *io, struct elevator *ele){
    struct order *buttonOrder = buttonCallback();
    
        //setButtonLights(io, buttonOrder, ele);
    io->orderArray = (struct order*) realloc(io->orderArray, io->size * sizeof(struct order));
    io->orderArray[io->size++] = buttonOrder;
    
}

void printOrderArray(struct IO *io){
    for(int i = 0; i < io->size; i++){
        printf("Order %d: Floor: %d, Button: %d\n", i, io->orderArray[i]->floor, io->orderArray[i]->button);
    }
}
