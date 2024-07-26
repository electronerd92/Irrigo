#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <Arduino.h>

// Define log levels
enum class LogLevel : byte
{
    INFO,
    ALERT
};

// Ensure Serial initialization is only performed once
inline void initializeSerial()
{
    static bool serialBegun = false; // Static variable to track initialization
    if (!serialBegun)
    {
        Serial.begin(9600);
        serialBegun = true;
    }
}

template <typename T>
inline void debugLog(const T &message, LogLevel level = LogLevel::INFO)
{
    debugLog(message, "", level);
}

// General-purpose debugLog function
template <typename T, typename S>
inline void debugLog(const T &message, const S &messageLoad, LogLevel level = LogLevel::INFO)
{
#if DEBUG > 0
    initializeSerial(); // Ensure serial is initialized

    // Determine if the message should be printed based on DEBUG level
    if (DEBUG == 1 || (DEBUG == 2 && level == LogLevel::ALERT))
    {
        switch (level)
        {
        case LogLevel::ALERT:
            Serial.print("[ALERT] ");
            break;
        case LogLevel::INFO:
        default:
            Serial.print("[INFO] ");
            break;
        }

        Serial.print(message);
        Serial.println(messageLoad);
    }
#endif
}

#endif // DEBUG_HPP