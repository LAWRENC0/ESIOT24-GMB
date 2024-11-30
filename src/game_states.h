#include "game_logic.h"
#include "interrupts.h"
#include "visuals.h"
#include "input.h"

#define SECONDS(x) ((x) * 1000)
#define DELAY_TIME 25

int welcomePhase();

int check1();

int sleepingPhase();

int gamePhase0();

int gamePhase1();

int check2(int to_guess);

int gamePhase2();

int endPhase();

