#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

const uint8_t BUFFER_SIZE = 12;

// Define pinout for the rotary
const uint8_t ROTARY_PIN_A = 3;
const uint8_t ROTARY_PIN_B = 2;
const uint8_t ROTARY_BUTTON_PIN = 4;

// Define LCD parameters
const uint8_t LCD_ADDRESS = 0x27;
const uint8_t LCD_COLUMNS = 20;
const uint8_t LCD_ROWS = 4;
const unsigned long LCD_TIME_ON = 60000;      // ms
const unsigned long LCD_BLINK_INTERVAL = 500; // ms

// Pinout Irrigation Valves
const uint8_t PIN_VALVE_1 = 10;
const uint8_t PIN_VALVE_2 = 11;
const uint8_t PIN_VALVE_3 = 12;
const uint8_t PIN_VALVE_4 = 13;
const uint8_t PIN_VALVE_5 = 14;
const uint8_t PIN_VALVE_6 = 15;
const uint8_t PIN_VALVE_7 = 16;
const uint8_t PIN_VALVE_8 = 17;

// Pinout Valves
const uint8_t PIN_VALVE_EXT = 20;
const uint8_t PIN_VALVE_PUMP = 18;
const uint8_t PIN_VALVE_MAIN = 19;

#endif // PROJECT_CONFIG_H