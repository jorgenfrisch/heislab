#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "elevio.h"
#include "elevator.h"


typedef struct{
    int floor;
    ButtonType button;
} order;

typedef struct {
    bool floorLight;
    int orderDirection;
    int orderFloor;
    bool stop;
    bool obstruction;
    int recentFloor;
    order** orderArray;
    int size;
} IO;

void initializeIO(IO *io);
void setFloorLights(IO *io);
void setButtonLight(IO *io, order *order, struct elevator *ele);
void turnOfButtonLight(IO *io, order *order, struct elevator *ele);
void setOrders(IO *io, struct elevator *ele);
order* buttonCallback();
void printOrderArray(IO *io);
void freeOrderArray(IO *io);