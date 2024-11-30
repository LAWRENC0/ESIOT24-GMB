#include <Arduino.h>

#include "GMB_Elaborato1.h"
#include "interrupts.h"

void B0ManagerNOLEDs(){
  if(DEBUG >= 2)Serial.println("Pressed B0 no LEDS");
	buttonPressedUpdater(0, FALSE);
}

void B0Manager(){
  if(DEBUG >= 2)Serial.println("Pressed B0");
	buttonPressedUpdater(0, TRUE);
}

void B1Manager(){
  if(DEBUG >= 2)Serial.println("Pressed B1");
	buttonPressedUpdater(1, TRUE);
}

void B2Manager(){
  if(DEBUG >= 2)Serial.println("Pressed B2");
	buttonPressedUpdater(2, TRUE);
}

void B3Manager(){
  if(DEBUG >= 2)Serial.println("Pressed B3");
	buttonPressedUpdater(3, TRUE);
}

int isNotBouncing(int button_number){
	static unsigned long buttons_last_hit_time[4] = {0,0,0,0};
	unsigned long current_hit_time = millis();
  if(DEBUG >= 1){
    Serial.print("BLHT ");
    Serial.print(button_number);
    Serial.print(" ");
    Serial.print(buttons_last_hit_time[button_number]);
    Serial.print(" ");
  }
	if(current_hit_time - buttons_last_hit_time[button_number] > BOUNCE_TIME){
    if(DEBUG >= 1){
      Serial.print("not bounce");
      Serial.println("");
    }
	  buttons_last_hit_time[button_number] = current_hit_time;
		return TRUE;
	}
  if(DEBUG >= 1){
    Serial.print("bounce");
    Serial.println("");
  }
  return false;
}

void buttonPressedUpdater(int button_number, int affect_LEDs){
	if(isNotBouncing(button_number)){
		buttons_pressed_shared[button_number] = 1 - buttons_pressed_shared[button_number];
    if(DEBUG >= 2){
      Serial.print("BUPD: bN ");
      Serial.print(button_number);
      Serial.print(" state: ");
      Serial.print(buttons_pressed_shared[button_number]);
    }
    if(affect_LEDs){
      greenLEDsBlink(buttons_pressed_shared);
    }
	}
}

void myWakeUp(){
  if(DEBUG >= 1)Serial.println("WakeUp:");
}