#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "System.h"
#include "Debug.hpp"
#include "menu/Menu.h"
#include "menu/MenuCallbacks.h"
#include "menu/NavigableMenu.h"
#include "menu/CallableMenu.h"
#include "menu/CommandManager.h"
#include "menu/ValveSettingsMenu.h"
#include "menu/LCDManager.h"
#include "irrigationSystem/IrrigationSystem.h"

void initializeMenus();

void setup()
{
  debugLog("Starting ...");
  initializeMenus();
}

void loop()
{
  System::getInstance().update();
  Menu::getInstance().update();
  CommandManager::getInstance().update();
  LCDManager::getInstance().update();
  IrrigationSystem::getInstance().update();
}

// Initialize menus with callbacks from MenuCallbacks
void initializeMenus()
{
  // Create menu items
  NavigableMenu *mainMenu = new NavigableMenu(F("Main"), 6);
  NavigableMenu *settingsMenu = new NavigableMenu(F("Settings"), 2);
  CallableMenu *infoMenu = new CallableMenu(F("Info"), &MenuCallbacks::printInfo);
  CallableMenu *factoryResetMenu = new CallableMenu(F("Factory Reset"), &MenuCallbacks::resetToFactorySettings);

  mainMenu->addSubItem(settingsMenu);
  mainMenu->addSubItem(infoMenu);
  mainMenu->addSubItem(factoryResetMenu);

  NavigableMenu *settingsValvesMenu = new NavigableMenu(F("Valves"), 8);
  NavigableMenu *settingsSystemMenu = new NavigableMenu(F("System"), 2);

  settingsMenu->addSubItem(settingsValvesMenu);
  settingsMenu->addSubItem(settingsSystemMenu);

  ValveSettingsMenu::createInstance(settingsMenu);
  settingsValvesMenu->addSubItem(new CallableMenu(F("V1"), &MenuCallbacks::selectValve1));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V2"), &MenuCallbacks::selectValve2));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V3"), &MenuCallbacks::selectValve3));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V4"), &MenuCallbacks::selectValve4));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V5"), &MenuCallbacks::selectValve5));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V6"), &MenuCallbacks::selectValve6));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V7"), &MenuCallbacks::selectValve7));
  settingsValvesMenu->addSubItem(new CallableMenu(F("V8"), &MenuCallbacks::selectValve8));

  settingsSystemMenu->addSubItem(new CallableMenu(F("Date"), &MenuCallbacks::setDate));
  settingsSystemMenu->addSubItem(new CallableMenu(F("Time"), &MenuCallbacks::setTime));

  // Create the menu instance
  Menu::createInstance(mainMenu);
}