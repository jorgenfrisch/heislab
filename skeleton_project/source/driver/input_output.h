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
    struct order** orderArray;
    int size;
};

void initializeIO(struct IO *io);
void setFloorLights(struct IO *io);
void setButtonLights(struct IO *io, struct order *order, struct elevator *ele);
void setOrders(struct IO *io, struct elevator *ele);
void printOrderArray(struct IO *io);
struct order* buttonCallback();

struct order{
    int floor;
    ButtonType button;
};

