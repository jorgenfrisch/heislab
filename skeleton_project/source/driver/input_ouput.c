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
//Is used to turn on button light when an order is placed
void setButtonLight(struct IO *io, struct order *order, struct elevator *ele){
    elevio_buttonLamp(order->floor, order->button, 1);
}
//is used to turn of button light when a order is terminated 
void turnOfButtonLight(struct IO *io, struct order *order, struct elevator *ele){
    elevio_buttonLamp(order->floor, order->button, 0);
}
/* struct order* buttonCallback(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
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
        io->orderArray[io->size] = buttonCallback();
        
    }
} */


struct order* buttonCallback() {
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed == 1) {
                struct order *buttonOrder = malloc(sizeof(struct order));
                if (buttonOrder != NULL) { // Check if malloc succeeded
                    buttonOrder->floor = f;
                    buttonOrder->button = b;
                    return buttonOrder;
                } else {
                    // Handle malloc failure
                    return NULL;
                }
            }
        }
    }
    return NULL; // No button pressed, return NULL
}

void setOrders(struct IO *io, struct elevator *ele) {
    struct order *newOrder = buttonCallback();
    if (newOrder != NULL) {
        for(int i = 0; i<io->size; i++){
        if(io->orderArray[i]->button==newOrder->button && io->orderArray[i]->floor==newOrder->floor){
            free(newOrder);
            return;
        }
    }
        setButtonLight(io, newOrder, ele);
        io->size++;
        io->orderArray = realloc(io->orderArray, io->size * sizeof(struct order *));
        if (io->orderArray != NULL) { // Check if realloc succeeded
            io->orderArray[io->size - 1] = newOrder; // Assign the pointer to the new order
        } else {
            // Handle realloc failure
            free(newOrder); // Free the memory allocated in buttonCallback
        }
    }
}

void printOrderArray(struct IO *io) {
    printf("Printing orderArray:\n");
    for (size_t i = 0; i < io->size; i++) {
        struct order *currentOrder = io->orderArray[i];
        printf("Order %zu: Floor: %d, Button: %d\n", i, currentOrder->floor, currentOrder->button);
    }
}


void freeOrderArray(struct IO *io) {
    if (io->orderArray != NULL) {
        // Free memory for each struct order pointer in orderArray
        for (size_t i = 0; i < io->size; i++) {
            free(io->orderArray[i]);
        }
        // Free memory allocated for orderArray itself
        free(io->orderArray);
        io->orderArray = NULL; // Reset orderArray pointer to NULL
        io->size = 0; // Reset size to 0
    }
}

