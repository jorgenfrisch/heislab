#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "elevio.h"

struct elevator
{
    int currentFloor;
    MotorDirection motorDir;
    int doorOpen;
    time_t t;
    time_t clock;
    bool obstruction;
    MotorDirection lastmotorDir;
};

void initializeElevator(struct elevator *ele);
void doorOpens(struct elevator *ele);
void setObstruction(struct elevator *ele);
void timerStart(struct elevator *ele);
int checkTimer(time_t clock, time_t t);

/* void emergencyStop(void);
void startUp(int timer);
void stopButton();
void initializeElevator(elevator *elevator, int currentFloor);
 */
