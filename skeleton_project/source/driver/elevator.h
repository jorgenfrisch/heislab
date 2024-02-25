
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "elevio.h"


struct elevator {
    int currentFloor;
    MotorDirection motorDir;
    bool isMoving;
    bool doorOpen;
    int targetFloor;
    int timer;
};

void initializeElevator(struct elevator *elevator, int currentFloor);

void moveTo(struct elevator *elevator, int target);

/* void emergencyStop(void);
void openDoor(...);
void startUp(int timer);
void stopButton();
void initializeElevator(struct elevator *elevator, int currentFloor);
 */
