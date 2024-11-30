#include <Arduino.h>

#include "GMB_Elaborato1.h"
#include "game_logic.h"

// Update difficulty variable
void updateDifficulty(int new_difficulty){
	difficulty = new_difficulty;
  if(DEBUG >= 1){
    Serial.print("Update Difficulty: ");
    Serial.print(difficulty);
    Serial.println("");
  }
}

void updateFValue(){
	f = (float)difficulty / 10;
  if(DEBUG >= 1){
    Serial.print("Update FValue: ");
    Serial.print(f);
    Serial.println("");
  }
}

void increaseRound(){
  current_round++;
  if(DEBUG >= 1){
    Serial.print("Increase Round: ");
    Serial.print(current_round);
    Serial.println("");
  }
}

// Update score variable based on current round and difficulty
void updateScore(){
	score = score + (int)((f + 1) * 10 + (DEFAULT_ROUND_DURATION / round_duration) * 0.5 * current_round);
  if(DEBUG >= 1){
    Serial.print("Update Score: ");
    Serial.print(score);
    Serial.println("");
  }
}

// Update time variable based on current round and difficulty
void updateRoundDuration(){
  round_duration = (long)(round_duration * (float)(1 - 0.4*f));
  if(DEBUG >= 1){
    Serial.print("Update Round Duration: ");
    Serial.print(round_duration);
    Serial.println("");
  }
}

// funciton which returns random value
int getNumberToGuess(){
  return random(16);
}

void myDelay(long time_to_wait){
  //if(DEBUG)Serial.println("Delay: " + time_to_wait);
  unsigned long u_time_to_wait = (unsigned long)time_to_wait;
  unsigned long ts = millis();
  for(;millis() - ts < u_time_to_wait;){}
}