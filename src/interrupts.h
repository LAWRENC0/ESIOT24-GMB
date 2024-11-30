#include "visuals.h"

#define BOUNCE_TIME 250

#define FALSE 0
#define TRUE 1

void B0ManagerNOLEDs();

void B0Manager();

void B1Manager();

void B2Manager();

void B3Manager();

int isNotBouncing(int button_number);

void buttonPressedUpdater(int button_number, int affect_LEDs);

void myWakeUp();