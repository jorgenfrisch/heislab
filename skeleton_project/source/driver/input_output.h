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
};

/* void setStop();
void setObstruction();
void setOrderedDirection();
void setOrderedFloor();
void setFloorLight(int floor);

 */