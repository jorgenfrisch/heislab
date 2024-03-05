#include "input_output.h"
#include "elevator.h"


void initializeIO(IO *io){
    io->size = 0;
    io->orderArray = NULL;
    io->orderArray = (order*)malloc(io->size*sizeof(order));
}

void setFloorLights( IO *io){
   if(elevio_floorSensor()!=-1 && elevio_floorSensor()!=io->recentFloor){
    io->recentFloor = elevio_floorSensor();
    elevio_floorIndicator(io->recentFloor);
   }
}
void setButtonLight(IO *io, order *order, struct elevator *ele){
    elevio_buttonLamp(order->floor, order->button, 1);
}
void turnOfButtonLight(IO *io, order *order, struct elevator *ele){
    elevio_buttonLamp(order->floor, order->button, 0);
}


order* buttonCallback() {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1) {
                order *buttonOrder = malloc(sizeof(order));
                if (buttonOrder != NULL) { 
                    buttonOrder->floor = f;
                    buttonOrder->button = b;
                    return buttonOrder;
                } else {
                    return NULL;
                }
            }
        }
    }
    return NULL; 
}

void setOrders(IO *io, struct elevator *ele) {
    order *newOrder = buttonCallback();
    if (newOrder != NULL) {
        for(int i = 0; i<io->size; i++){
        if(io->orderArray[i]->button==newOrder->button && io->orderArray[i]->floor==newOrder->floor){
            free(newOrder);
            return;
        }
    }
        setButtonLight(io, newOrder, ele);
        io->size++;
        io->orderArray = realloc(io->orderArray, io->size * sizeof(order *));
        if (io->orderArray != NULL) { 
            io->orderArray[io->size - 1] = newOrder; 
        } else {

            free(newOrder); 
        }
    }
}

void printOrderArray(IO *io) {
    printf("Printing orderArray:\n");
    for (size_t i = 0; i < io->size; i++) {
        order *currentOrder = io->orderArray[i];
        printf("Order %zu: Floor: %d, Button: %d\n", i, currentOrder->floor, currentOrder->button);
    }
}


void freeOrderArray(IO *io) {
    if (io->orderArray != NULL) {
        for (size_t i = 0; i < io->size; i++) {
            free(io->orderArray[i]);
        }
        free(io->orderArray);
        io->orderArray = NULL; 
        io->size = 0; 
    }
}

