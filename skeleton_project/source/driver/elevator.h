#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "elevio.h"


struct elevator{
    int currentFloor;
    MotorDirection motorDir;
    bool doorOpen;
    int targetFloor;
    int timer;
    int orderTaken;
    int targetDirection;
};

void initializeElevator(struct elevator *ele);



/* void emergencyStop(void);
void openDoor(...);
void startUp(int timer);
void stopButton();
void initializeElevator(elevator *elevator, int currentFloor);
 */
