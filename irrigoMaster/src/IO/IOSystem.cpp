#include "IOSystem.h"
#include "../ProjectConfig.h"
#include "../Irrigation/IrrigationSystem.h"
#include "CustomTypes.h"

IOSystem::IOSystem(MainSystem *mainSystem)
    : mainSystem(mainSystem),
      irrigationSystem(mainSystem->getIrrigationSystem()),
      lcd(),
      rotaryEncoder(),
      menu(&lcd, &rotaryEncoder, this)
{
}

void IOSystem::update()
{
  rotaryEncoder.update();
  menu.update();
  lcd.update();
}

void IOSystem::initValveIndex()
{
  irrigationSystem->setValveIndex(0);
}

const char *IOSystem::getValveIndex()
{
  uint8_t value = irrigationSystem->getValveIndex() + 1;
  snprintf(buffer, BUFFER_SIZE, "%u", value);
  return buffer;
}

void IOSystem::setValveIndex(bool goUp)
{
  int delta = goUp == true ? +1 : -1;
  irrigationSystem->setValveIndex(irrigationSystem->getValveIndex() + delta);
}

const char *IOSystem::getValveMode()
{
  ValveMode value = irrigationSystem->getValveMode();

  switch (value)
  {
  case ValveMode::OFF:
    return "OFF";

  case ValveMode::TIMER:
    return "TIMER";
  }
}

void IOSystem::setValveMode(bool goUp)
{
  ValveMode currentMode = irrigationSystem->getValveMode();
  int modeCount = static_cast<int>(ValveMode::COUNT);

  int newMode = static_cast<int>(currentMode) + (goUp ? 1 : -1);
  newMode = (newMode + modeCount) % modeCount; // Circular wrap-around

  irrigationSystem->setValveMode(static_cast<ValveMode>(newMode));
}

const char *IOSystem::getValveStartTime()
{
  if (irrigationSystem->getValveMode() == ValveMode::OFF)
  {
    return "-";
  }
  Time_HHMM value = irrigationSystem->getValveStartTime();
  snprintf(buffer, BUFFER_SIZE, "%02u:%02u", value.hour, value.minute);
  return buffer;
}
void IOSystem::setValveStartTimeHour(bool goUp)
{
  uint8_t currentHour = irrigationSystem->getValveStartTime().hour;
  uint8_t newHour = goUp ? (currentHour + 1) % 24 : (currentHour + 23) % 24;
  irrigationSystem->setValveStartTimeHour(newHour);
}

void IOSystem::setValveStartTimeMinute(bool goUp)
{
  uint8_t currentMinute = irrigationSystem->getValveStartTime().minute;
  uint8_t newMinute = goUp ? (currentMinute + 5) % 60 : (currentMinute + 55) % 60;
  irrigationSystem->setValveStartTimeMinute(newMinute);
}

const char *IOSystem::getValveFrequency()
{
  if (irrigationSystem->getValveMode() == ValveMode::OFF)
  {
    return "-";
  }
  uint8_t value = irrigationSystem->getValveFrequency();
  snprintf(buffer, BUFFER_SIZE, "%u", value);
  return buffer;
}

void IOSystem::setValveFrequency(bool goUp)
{
  int delta = goUp == true ? +6 : -6;
  irrigationSystem->setValveFrequency(irrigationSystem->getValveFrequency() + delta);
}

const char *IOSystem::getValveDuration()
{
  if (irrigationSystem->getValveMode() == ValveMode::OFF)
  {
    return "-";
  }
  uint8_t value = irrigationSystem->getValveDuration();
  snprintf(buffer, BUFFER_SIZE, "%u", value);
  return buffer;
}

void IOSystem::setValveDuration(bool goUp)
{
  int delta = goUp == true ? +1 : -1;
  irrigationSystem->setValveDuration(irrigationSystem->getValveDuration() + delta);
}
