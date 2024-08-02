#include <Arduino.h>
#include <Wire.h>

#include "Debug.hpp"
#include "menu/Menu.h"
#include "menu/NavigableMenu.h"
#include "menu/CallableMenu.h"
#include "menu/Command.h"
#include "menu/CommandManager.h"
#include "menu/LCDManager.h"

bool printHello1(Command cmd);
bool printInfo(Command cmd);

// Global pointers
Menu *menu = nullptr;
CommandManager *commandManager = nullptr;

void setup()
{
  debugLog(F("Starting setup..."));

  // // Create menu items
  NavigableMenu *mainMenu = new NavigableMenu(F("Main"), 6);
  NavigableMenu *settingsMenu = new NavigableMenu(F("Settings"), 1);
  CallableMenu *infoMenu = new CallableMenu(F("Info"), printInfo);

  mainMenu->addSubItem(settingsMenu);
  mainMenu->addSubItem(infoMenu);

  CallableMenu *settingsV1 = new CallableMenu(F("V1 settings"), printHello1);

  settingsMenu->addSubItem(settingsV1);

  // Create the menu instance
  Menu::createInstance(mainMenu);
}

void loop()
{
  Menu::getInstance().update();
  CommandManager::getInstance().update();
  LCDManager::getInstance().update();
}

bool printHello1(Command cmd)
{
  debugLog(F("printHello1 "));

  if (cmd == Command::SELECT)
    return false; // exit
  return true;
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