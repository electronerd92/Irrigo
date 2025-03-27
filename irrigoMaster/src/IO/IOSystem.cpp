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

const char *IOSystem::getIrrigationSystemMode()
{
  uint8_t value = irrigationSystem->getMode();

  switch (value)
  {
  case OFF:
    return "OFF";

  case ON:
    return "ON";

  default:
    return "ERR";
  }
}

void IOSystem::setIrrigationSystemMode(bool goUp)
{
  irrigationSystem->setMode(irrigationSystem->getMode() ^ 1); // xor to iterate 0 and 1
}

const char *IOSystem::getWaterFeederType()
{
  WaterFeederType value = irrigationSystem->getWaterFeederType();

  switch (value)
  {
  case WaterFeederType::MAIN:
    return "MAIN";

  case WaterFeederType::PUMP:
    return "PUMP";

  default:
    return "ERR";
  }
}

void IOSystem::setWaterFeederType(bool goUp)
{
  WaterFeederType currentWaterFeederType = irrigationSystem->getWaterFeederType();
  int WaterFeederTypeCount = static_cast<int>(WaterFeederType::COUNT);

  int newWaterFeederType = static_cast<int>(currentWaterFeederType) + (goUp ? 1 : -1);
  newWaterFeederType = (newWaterFeederType + WaterFeederTypeCount) % WaterFeederTypeCount; // Circular wrap-around

  irrigationSystem->setWaterFeederType(static_cast<WaterFeederType>(newWaterFeederType));
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

  default:
    return "ERR";
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
  constexpr uint8_t delta = 12;
  uint8_t currentFrequency = irrigationSystem->getValveFrequency();
  if (goUp && currentFrequency <= 255 - delta)
  {
    irrigationSystem->setValveFrequency(currentFrequency + delta);
  }
  else if (!goUp && currentFrequency >= delta)
  {
    irrigationSystem->setValveFrequency(currentFrequency - delta);
  }
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
  constexpr uint8_t delta = 1;
  uint8_t currentDuration = irrigationSystem->getValveDuration();
  if (goUp && currentDuration <= 255 - delta)
  {
    irrigationSystem->setValveDuration(currentDuration + delta);
  }
  else if (!goUp && currentDuration >= delta)
  {
    irrigationSystem->setValveDuration(currentDuration - delta);
  }
}
