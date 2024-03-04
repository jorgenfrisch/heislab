#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "input_output.h"




//void runEle(struct IO *io, struct elevator *ele);

// void removeOrder(IO *io, struct elevator *ele){
//     for (int i = 0; i < io->size; i++){
//         if (io->orderArray[i]->floor == ele->currentFloor){
//             if (io->orderArray[i]->button == ele->motorDir)
//         }
//     }

// }

void moveTo(struct elevator *ele, IO *io);
void removeOrder(IO *io, int index);