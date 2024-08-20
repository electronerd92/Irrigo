#include <Arduino.h>
#include <Wire.h>

// put function declarations here:
int myFunction(int, int);

enum class ValveMode : byte
{
    OFF,
    CLASSIC,
    SMART
};

struct FlashStringWithLength
{
  const __FlashStringHelper *str;
  size_t length;
};

static FlashStringWithLength valveModeToString(ValveMode mode)
{
  FlashStringWithLength result;
  switch (mode)
  {
  case OFF:
    result.str = F("OFF");
    result.length = strlen_P((const char *)result.str);
    break;
  case CLASSIC:
    result.str = F("CLASSIC");
    result.length = strlen_P((const char *)result.str);
    break;
  case SMART:
    result.str = F("SMART");
    result.length = strlen_P((const char *)result.str);
    break;
  default:
    result.str = F("UNKNOWN");
    result.length = strlen_P((const char *)result.str);
    break;
  }
  return result;
}

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}