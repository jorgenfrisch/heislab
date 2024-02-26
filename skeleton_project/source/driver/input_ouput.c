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
            printf("%d",btnPressed);
            if (btnPressed == 1){
                struct order *buttonOrder = malloc(sizeof(struct order));
                buttonOrder->floor = f;
                buttonOrder->button = b;
                return buttonOrder;
            }
        }
    }
    return NULL; // Add a return statement for the case when no button is pressed
}

void setOrders(struct IO *io, struct elevator *ele){
    if (buttonCallback() != NULL){
        setButtonLights(io, buttonCallback(), ele);
        io->size++;
        io->orderArray = (struct order*) realloc(io->orderArray, io->size * sizeof(struct order));
        if (io->orderArray == NULL) {
            // Handle memory allocation failure
            free(buttonCallback());
            return;
        }
        io->orderArray[io->size] = buttonCallback();
        
    }
}


/*  void setOrders(struct IO *io, struct elevator *ele){
    struct order *buttonOrder = buttonCallback();
    io->size++;
    if (buttonOrder != NULL) {
        setButtonLights(io, buttonOrder, ele);
        io->orderArray = realloc(io->orderArray, (io->size) * sizeof(struct order));
        if (io->orderArray == NULL) {
            // Handle memory allocation failure
            free(buttonOrder);
            return;
        }
        io->orderArray[io->size] = &buttonOrder;
        free(buttonOrder); // Free the memory allocated by buttonCallback
    }
} */
void printOrderArray(struct IO *io){
    for(int i = 0; i < 1; i++){
        printf("Order %d: Floor: %d, Button: %d\n", i, io->orderArray[i]->floor, io->orderArray[i]->button);
    }
}
