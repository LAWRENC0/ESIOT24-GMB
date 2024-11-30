#include <LiquidCrystal_I2C.h>

#define LS_PIN 3  // pwm out -> needs to be analog
#define L0_PIN 2  // digital output pin
#define L1_PIN 4  // digital output pin
#define L2_PIN 7  // digital output pin
#define L3_PIN 8  // digital output pi
#define POT_PIN A0 // analog input pin
#define B0_PIN 13  // input pin
#define B1_PIN 12  // input pin
#define B2_PIN 11  // input pin
#define B3_PIN 10  // input pin

#define DEFAULT_ROUND_DURATION 8000

#define INITIAL_SCORE 0

#define WELCOME_PHASE 0
#define SLEEPING_PHASE 1
#define GAME_PHASE_0 2
#define GAME_PHASE_1 3
#define GAME_PHASE_2 4
#define END_PHASE 5

#define DEBUG 1

extern int ls_pin;
extern int l_pins[4];
extern int pot_pin;
extern int b_pins[4];
extern int buttons_pressed_shared[4];
extern int current_round;
extern int current_phase;
extern int difficulty;
extern float f;
extern long round_duration;
extern int score;

void initializer();

LiquidCrystal_I2C getLcd();