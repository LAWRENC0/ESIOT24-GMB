#include <EnableInterrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>

#include "GMB_Elaborato1.h"
#include "game_states.h"
#include "interrupts.h"

// Green LEDs off
// Ls pulses (fade)
// LCD: Welcome Message
// Potentiometer sets difficulty (modify f)
int welcomePhase(){
  if(DEBUG >= 2)Serial.println("Welcome Phase:");
  initializer();
  redLEDBlink(RED_LED_OFF);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_WELCOME_MESSAGE);
  int check_outcome = check1();
  redLEDBlink(RED_LED_OFF);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
  return check_outcome;
}

// B1 pression: interrupt
// 10 seconds: timer
// if B1 is pressed: return GAME_PHASE
// if 10s passed: return SLEEPING_PHASE
// this must stop the instruction flow
int check1(){
  // ...
  if(DEBUG >= 2)Serial.println("Check 1");
  int was_B1_pressed = 0;
  enableInterrupt(b_pins[0],B0ManagerNOLEDs,RISING);
  long ts = millis();
  for(; millis() - ts < SECONDS(10);){
    redLEDBlink(RED_LED_PULSE);
    noInterrupts();
    was_B1_pressed = buttons_pressed_shared[0];
    if(was_B1_pressed){
      break;
    }
    interrupts();
    //delay(DELAY_TIME); // !!!??? int o non int
    myDelay(DELAY_TIME);
  }
  interrupts();
  disableInterrupt(b_pins[0]);
  if(was_B1_pressed){
    if(DEBUG >= 2)Serial.println("Check 1: a button was pressed");
    return GAME_PHASE_0;
  }else{
    if(DEBUG >= 2)Serial.println("Check 1: no button was pressed");
    return SLEEPING_PHASE;
  }
}

// setup an interrupt for any button
// which wakes up arduino then set it to deep sleep
// then go to welcome phase
int sleepingPhase(){
  LiquidCrystal_I2C lcd = getLcd();
  if(DEBUG >= 1)Serial.println("Sleeping Phase:");
  // ...
  for(int i=0; i<4; i++){
    enableInterrupt(b_pins[i], myWakeUp, RISING);
  }
  if(DEBUG >= 1)Serial.println("Sleeping Phase: Going to sleep...");
  lcd.noBacklight();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  lcd.backlight();
  if(DEBUG >= 1)Serial.println("Sleeping Phase: Woke up!");
  for(int i=0; i<4; i++){
    disableInterrupt(b_pins[i]);
  }
  return WELCOME_PHASE;
}

// All LEDs off
// LCD: GO Message
// score must be set to zero
int gamePhase0(){
  if(DEBUG >= 2)Serial.println("Game Phase 0");
  if(current_round == 0){
    updateDifficulty(potentiometerRead());
    updateFValue();
  }
  updateRoundDuration();
  int g_LEDs_off[4] = {0,0,0,0};
  greenLEDsBlink(g_LEDs_off);
  redLEDBlink(RED_LED_OFF);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_GO_MESSAGE);
  // add an appropriate delay (bloccante) to let user read
  myDelay(SECONDS(2));
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
  return GAME_PHASE_1;
}

// All LEDs off
// LCD: random number
int gamePhase1(){
  if(DEBUG >= 2)Serial.println("Game Phase 0");
  int g_LEDs_off[4] = {0,0,0,0};
  for(int i=0; i<4; i++){
    buttons_pressed_shared[i] = 0;
  }
  greenLEDsBlink(g_LEDs_off);
  redLEDBlink(RED_LED_OFF);
  int to_guess = getNumberToGuess();
  LCDDisplay(LCD_NUMBER_MODE, to_guess);
  int check_outcome = check2(to_guess);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
  greenLEDsBlink(g_LEDs_off);
  if(check_outcome){
    return GAME_PHASE_2;
  }else{
    return END_PHASE;
  }
}

// set a timer of round_time seconds
// when it is up do a digital read of the numbers
// check correctness
// it must stop the instruction flow
int check2(int to_guess){
  //...
  if(DEBUG >= 2)Serial.println("Check 2");
  enableInterrupt(b_pins[0],B0Manager,RISING);
  enableInterrupt(b_pins[1],B1Manager,RISING);
  enableInterrupt(b_pins[2],B2Manager,RISING);
  enableInterrupt(b_pins[3],B3Manager,RISING);
  myDelay(round_duration);
  for(int i=0; i<4; i++){
    disableInterrupt(b_pins[i]);
  }
  int base_factor = 1;
  int guessed = 0;
  for(int i=0; i<4; i++){
    guessed = guessed + buttons_pressed_shared[3-i]*base_factor;
    base_factor = base_factor*2;
    buttons_pressed_shared[3-i] = 0;
  }
  if(DEBUG >= 1){
    Serial.print("\nGuessed: ");
    Serial.print(guessed);
    Serial.println("");
  }
  if(guessed == to_guess){
    return 1;
  }else{
    return 0;
  }
}

// increase score
// Success message
// reduce time available
int gamePhase2(){
  if(DEBUG >= 2)Serial.println("Game Phase 2:");
  increaseRound();
  updateScore();
  updateRoundDuration();
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_SUCCESS_MESSAGE);
  //delay(DELAY_TIME); // !!!??? int o non int
  myDelay(SECONDS(3));
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
  return GAME_PHASE_0;
}

// Ls on for 1 sec
// LCD: game over...
int endPhase(){
  if(DEBUG >= 2)Serial.println("End Phase:");
  long ts = millis();
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_GAMEOVER_MESSAGE);
  for(; millis() - ts < SECONDS(10);){
    if(millis() - ts < SECONDS(1)){
      redLEDBlink(RED_LED_PULSE);
    }
  }
  //delay(DELAY_TIME); // !!!??? int o non int
  myDelay(DELAY_TIME);
  LCDDisplay(LCD_DEF_MSG_MODE, LCD_OFF);
  return WELCOME_PHASE;
}