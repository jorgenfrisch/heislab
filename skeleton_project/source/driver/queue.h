#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "input_output.h"


void moveTo(struct elevator *ele, IO *io);
void removeOrder(IO *io, int index);