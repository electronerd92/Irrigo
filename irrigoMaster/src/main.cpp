#include <Arduino.h>
#include <Wire.h>

#include "Debug.hpp"
#include "menu/Menu.h"
#include "menu/MenuItem.h"
#include "menu/Command.h"
#include "menu/CommandManager.h"
#include "menu/LCDManager.h"

bool printHello1(Command cmd);
bool printHello2(Command cmd);

// Global pointers
Menu *menu = nullptr;
CommandManager *commandManager = nullptr;

void setup()
{
  debugLog(F("Starting setup..."));

  // Create menu items
  MenuItem *mainMenu = new MenuItem(F("Main"), 2);
  MenuItem *submenu1 = new MenuItem(F("Sub1"), printHello1);
  MenuItem *submenu2 = new MenuItem(F("Sub2"), printHello2);
  mainMenu->addSubItem(submenu1);
  mainMenu->addSubItem(submenu2);

  // Create the menu instance
  menu = &Menu::create(mainMenu);

  // Initialize the command manager instance
  commandManager = &CommandManager::getInstance();
}

void loop()
{
  menu->update();
  commandManager->update();
  
}

bool printHello1(Command cmd)
{
  debugLog(F("printHello1 "), cmd, LogLevel::INFO);

  if (cmd == Command::SELECT)
    return false; // exit
  return true;
}

bool printHello2(Command cmd)
{
  debugLog(F("printHello2 "), cmd, LogLevel::INFO);

  if (cmd == Command::SELECT)
    return false; // exit
  return true;
}