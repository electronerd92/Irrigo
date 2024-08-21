#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "System.h"
#include "Debug.hpp"
#include "menu/Menu.h"
#include "menu/NavigableMenu.h"
#include "menu/CallableMenu.h"
#include "menu/Command.h"
#include "menu/CommandManager.h"
#include "menu/ValveSettingsMenu.h"
#include "menu/LCDManager.h"
#include "irrigationSystem/IrrigationSystem.h"

void printValveSettingsMenu();
bool setV1(Command cmd);
bool setV2(Command cmd);
bool setV3(Command cmd);
bool setV4(Command cmd);
bool setV5(Command cmd);
bool setV6(Command cmd);
bool setV7(Command cmd);
bool setV8(Command cmd);
bool printInfo(Command cmd);

// Global pointers
Menu *menu = nullptr;
CommandManager *commandManager = nullptr;

void setup()
{
  // Create menu items
  NavigableMenu *mainMenu = new NavigableMenu(F("Main"), 6);
  NavigableMenu *settingsMenu = new NavigableMenu(F("Settings"), 8);
  CallableMenu *infoMenu = new CallableMenu(F("Info"), printInfo);

  mainMenu->addSubItem(settingsMenu);
  mainMenu->addSubItem(infoMenu);

  ValveSettingsMenu::createInstance(settingsMenu);

  CallableMenu *settingsV1 = new CallableMenu(F("V1 settings"), setV1);
  CallableMenu *settingsV2 = new CallableMenu(F("V2 settings"), setV2);
  CallableMenu *settingsV3 = new CallableMenu(F("V3 settings"), setV3);
  CallableMenu *settingsV4 = new CallableMenu(F("V4 settings"), setV4);
  CallableMenu *settingsV5 = new CallableMenu(F("V5 settings"), setV5);
  CallableMenu *settingsV6 = new CallableMenu(F("V6 settings"), setV6);
  CallableMenu *settingsV7 = new CallableMenu(F("V7 settings"), setV7);
  CallableMenu *settingsV8 = new CallableMenu(F("V8 settings"), setV8);

  settingsMenu->addSubItem(settingsV1);
  settingsMenu->addSubItem(settingsV2);
  settingsMenu->addSubItem(settingsV3);
  settingsMenu->addSubItem(settingsV4);
  settingsMenu->addSubItem(settingsV5);
  settingsMenu->addSubItem(settingsV6);
  settingsMenu->addSubItem(settingsV7);
  settingsMenu->addSubItem(settingsV8);

  // Create the menu instance
  Menu::createInstance(mainMenu);
}

void loop()
{
  Menu::getInstance().update();
  CommandManager::getInstance().update();
  LCDManager::getInstance().update();
  IrrigationSystem::getInstance().update();
}

void printValveSettingsMenu()
{
  Menu::getInstance().saveDisplayState();
  Menu::getInstance().setCurrentMenuItem(&ValveSettingsMenu::getInstance());
}

bool setV1(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(0));
  printValveSettingsMenu();
  return false;
}

bool setV2(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(1));
  printValveSettingsMenu();
  return false;
}

bool setV3(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(2));
  printValveSettingsMenu();
  return false;
}

bool setV4(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(3));
  printValveSettingsMenu();
  return false;
}

bool setV5(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(4));
  printValveSettingsMenu();
  return false;
}

bool setV6(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(5));
  printValveSettingsMenu();
  return false;
}

bool setV7(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(6));
  printValveSettingsMenu();
  return false;
}

bool setV8(Command cmd)
{
  ValveSettingsMenu::getInstance().setSource(IrrigationSystem::getInstance().getValve(7));
  printValveSettingsMenu();
  return false;
}

bool printInfo(Command cmd)
{
  static bool firstTime = true;

  if (firstTime)
  {
    firstTime = false;
    LCDManager::getInstance().clear();
    LCDManager::getInstance().print(F("Info..Press enter"));
    return true;
  }

  if (cmd == Command::SELECT && !firstTime)
  {
    firstTime = true;
    return false; // exit
  }
  return true;
}