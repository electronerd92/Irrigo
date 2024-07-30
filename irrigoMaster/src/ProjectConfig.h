#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

// Define pinout for the rotary
const uint8_t ROTARY_PIN_A = 3;
const uint8_t ROTARY_PIN_B = 2;
const uint8_t ROTARY_BUTTON_PIN = 4;

// Define LCD parameters
const uint8_t LCD_ADDRESS = 0x27;
const uint8_t LCD_COLUMNS = 20;
const uint8_t LCD_ROWS = 4;
const unsigned long LCD_TIME_ON = 10000; // ms

// You can add other project-wide configuration constants here

#endif // PROJECT_CONFIG_H