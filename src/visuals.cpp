#include <Arduino.h>

#include "GMB_Elaborato1.h"
#include "visuals.h"

void LCDDisplay(int LCD_display_mode, int LCD_display_message){
  LiquidCrystal_I2C lcd = getLcd();
  if(DEBUG >= 2)Serial.println("LCDDisplay:");
  if(LCD_display_mode == LCD_DEF_MSG_MODE){
    if(LCD_display_message == LCD_WELCOME_MESSAGE){
      //"Welcome to GMB! Press B1 to Start"
      lcd.print("Welcome to GMB!");
      lcd.setCursor(0, 1);
      lcd.print("Press B1 to Start");
    }else if(LCD_display_message == LCD_GO_MESSAGE){
      //"Go!"
      lcd.print("Go!");
    }else if(LCD_display_message == LCD_SUCCESS_MESSAGE){
      //"GOOD! Score: XXX"
      lcd.print("GOOD!:");
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.print(score);
    }else if(LCD_display_message == LCD_GAMEOVER_MESSAGE){
      //"Game Over - Final Score XXX"
      lcd.print("Game Over - ");
      lcd.setCursor(0, 1);
      lcd.print("Final Score ");
      lcd.print(score);
    }else if(LCD_display_message == LCD_OFF){
      //this must reset the LCD state
      lcd.clear();
      lcd.setCursor(0, 0);
    }
  }else if(LCD_display_mode == LCD_NUMBER_MODE){
    lcd.print(LCD_display_message);
      lcd.setCursor(0, 1);
  }
}

// Set the blinking moed for the green LEDs
// Supported modes are off or manual
void greenLEDsBlink(int* LEDs_state){
  if(DEBUG >= 2)Serial.print("Green Leds: ");
  for(int i=0; i<4; i++){
    if(DEBUG >= 2){
      Serial.print(LEDs_state[i]);
      Serial.print(" ");
    }
    digitalWrite(l_pins[i], LEDs_state[i]);
  }
  if(DEBUG >= 2)Serial.println("");
}

// Set the blinking mode for the red LED
// Supported modes are off and pulsing
void redLEDBlink(int red_LED_mode){
  static int fade_amount = 5;
  static int curr_intensity = 0;
  switch(red_LED_mode){
    case RED_LED_OFF: // this must turn red_led off
      if(DEBUG >= 2)Serial.println("Red Led: OFF");
      analogWrite(ls_pin, 0);
      break;
    case RED_LED_PULSE: // this must update the blink value
      //if(DEBUG)Serial.println("RED LED: FADE");
      analogWrite(ls_pin, curr_intensity);   
      curr_intensity = curr_intensity + fade_amount;
      if (curr_intensity == 0 || curr_intensity == 255) {
        fade_amount = -fade_amount ; 
      }     
      break;
    default:
      if(DEBUG>=0)Serial.println("Unexpected redLEDBlink mode");
  }
}

