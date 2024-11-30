// C++ code

#include "GMB_Elaborato1.h"
#include "game_states.h"

int ls_pin;
int l_pins[4];
int pot_pin;
int b_pins[4];
int buttons_pressed_shared[4];
int current_round;
int current_phase;
int difficulty;
float f;
long round_duration;
int score;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

void setup()
{
  Serial.begin(9600);
  
  ls_pin = LS_PIN;
  l_pins[0] = L0_PIN;
  l_pins[1] = L1_PIN;
  l_pins[2] = L2_PIN;
  l_pins[3] = L3_PIN;
  pot_pin = POT_PIN;
  b_pins[0] = B0_PIN;
  b_pins[1] = B1_PIN;
  b_pins[2] = B2_PIN;
  b_pins[3] = B3_PIN;

  pinMode(LS_PIN, OUTPUT);
  for(int i=0; i<4; i++) {
    pinMode(l_pins[i], OUTPUT);
    pinMode(b_pins[i], INPUT);
  }
  pinMode(POT_PIN, INPUT);

  current_phase = WELCOME_PHASE;
  initializer();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void initializer(){
  current_round = 0;
  round_duration = DEFAULT_ROUND_DURATION;
  score = INITIAL_SCORE;
  for(int i=0; i<4; i++) {
    buttons_pressed_shared[i] = 0;
  }
  int g_LEDs_off[4] = {0,0,0,0};
  greenLEDsBlink(g_LEDs_off);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
}

LiquidCrystal_I2C getLcd(){
  return lcd;
}

void loop()
{
  switch(current_phase){
    case WELCOME_PHASE:
      if(DEBUG >= 1)Serial.println("SL: Going in Welcome Phase");
      current_phase = welcomePhase();
      break;
    case SLEEPING_PHASE:
      if(DEBUG >= 1)Serial.println("SL: Going in Sleeping Phase");
      current_phase = sleepingPhase();
      break;
    case GAME_PHASE_0:
      if(DEBUG >= 1)Serial.println("SL: Going in Game Phase 0");
      current_phase = gamePhase0();
      break;
    case GAME_PHASE_1:
      if(DEBUG >= 1)Serial.println("SL: Going in Game Phase 1");
      current_phase = gamePhase1();
      break;
    case GAME_PHASE_2:
      if(DEBUG >= 1)Serial.println("SL: Going in Game Phase 2");
      current_phase = gamePhase2();
      break;
    case END_PHASE:
      if(DEBUG >= 1)Serial.println("SL: Going in End Phase 0");
      current_phase = endPhase();
      break;
    //ERROR
    default:
      if(DEBUG >= 0)Serial.println("Unexpected Game Phase");
  }
}