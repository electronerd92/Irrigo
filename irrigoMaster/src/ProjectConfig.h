#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

// EEPROM

const uint8_t EEPROM_VERSION_HIGH = 1;
const uint8_t EEPROM_VERSION_LOW = 0;

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

const uint32_t DELAY_OPENING_CLOSING_VALVE = 200; // ms

// Pinout Irrigation Valves
const uint8_t PIN_VALVE_1 = 10;
const uint8_t PIN_VALVE_2 = 11;
const uint8_t PIN_VALVE_3 = 12;
const uint8_t PIN_VALVE_4 = 13;
const uint8_t PIN_VALVE_5 = 14;
const uint8_t PIN_VALVE_6 = 15;
const uint8_t PIN_VALVE_7 = 16;
const uint8_t PIN_VALVE_8 = 17;

// IDs Irrigation Valves
const uint8_t ID_VALVE_1 = 1;
const uint8_t ID_VALVE_2 = 2;
const uint8_t ID_VALVE_3 = 3;
const uint8_t ID_VALVE_4 = 4;
const uint8_t ID_VALVE_5 = 5;
const uint8_t ID_VALVE_6 = 6;
const uint8_t ID_VALVE_7 = 7;
const uint8_t ID_VALVE_8 = 8;

// Pinout Valves
const uint8_t PIN_VALVE_EXT = 20;
const uint8_t PIN_VALVE_PUMP = 18;
const uint8_t PIN_VALVE_MAIN = 19;

// Pin Pump
const uint8_t PIN_PUMP = 30;

// Pin Water Level Sensor for tank
const uint8_t PIN_WLS_EMPTY = 31;
const uint8_t PIN_WLS_FULL = 32;

#endif // PROJECT_CONFIG_H