#include <Arduino.h>

#include "GMB_Elaborato1.h"
#include "input.h"

int potentiometerRead(){
  int pot_read = analogRead(pot_pin);
  if(DEBUG >= 1){
    Serial.print("Potentiometer Read: ");
    Serial.print(pot_read);
    Serial.println("");
  }
	return (pot_read / 256) + 1;
}