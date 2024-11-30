#define LCD_DEF_MSG_MODE 0
#define LCD_NUMBER_MODE 1
#define LCD_WELCOME_MESSAGE 0
#define LCD_GO_MESSAGE 1
#define LCD_SUCCESS_MESSAGE 2
#define LCD_GAMEOVER_MESSAGE 3
#define LCD_OFF 4

#define RED_LED_OFF 0
#define RED_LED_PULSE 1

void LCDDisplay(int LCD_display_mode, int LCD_display_message);

void greenLEDsBlink(int* LEDs_state);

void redLEDBlink(int red_LED_mode);
