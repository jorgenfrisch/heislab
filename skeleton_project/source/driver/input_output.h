#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "elevio.h"

struct IO{
    bool floorLight;
    int orderDirection;
    int orderFloor;
    bool stop;
    bool obstruction;
    int recentFloor;
    struct order* orders;
};

void initializeIO(struct IO *io);
void setStop();
void setObstruction();
void setOrderedDirection();
void setOrderedFloor();
void setOrders();
void setFloorLights(struct IO *io);
void setButtonLights(struct IO *io);


struct order{
    int floor;
    ButtonType button;
};

void initializeOrder(struct order *order);