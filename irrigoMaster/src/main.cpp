#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Debug.hpp"
#include "MainSystem.h"

// #include "System.h"
//
// #include "menu/Menu.h"
// #include "menu/MenuCallbacks.h"
// #include "menu/NavigableMenu.h"
// #include "menu/CallableMenu.h"
// #include "menu/CommandManager.h"
// #include "menu/ValveSettingsMenu.h"
// #include "menu/ShowNextIrrigationMenu.h"
// #include "menu/LCDManager.h"
// #include "irrigationSystem/IrrigationSystem.h"

// void initializeMenus();

MainSystem *mainSystem;

void setup()
{
  debugLog("Starting ...");
  mainSystem = new MainSystem();
  // initializeMenus();
  // System::getInstance().loadFromEEPROM();
}

void loop()
{
  mainSystem->update();
  // System::getInstance().update();
  // Menu::getInstance().update();
  // CommandManager::getInstance().update();
  // LCDManager::getInstance().update();
  // IrrigationSystem::getInstance().update();
}

//  // Initialize menus with callbacks from MenuCallbacks
//  void initializeMenus()
//  {
//    // Create menu items
//    NavigableMenu *mainMenu = new NavigableMenu(F("Main"), 2);
//    NavigableMenu *settingsMenu = new NavigableMenu(F("Settings"), 2);
//    NavigableMenu *infoMenu = new NavigableMenu(F("Info"), 2);
//
//    mainMenu->addSubItem(settingsMenu);
//    mainMenu->addSubItem(infoMenu);
//
//    NavigableMenu *settingsValvesMenu = new NavigableMenu(F("Valves settings"), 8);
//    NavigableMenu *settingsSystemMenu = new NavigableMenu(F("System settings"), 5);
//
//    settingsMenu->addSubItem(settingsValvesMenu);
//    settingsMenu->addSubItem(settingsSystemMenu);
//
//    ValveSettingsMenu::createInstance(settingsValvesMenu);
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V1"), &MenuCallbacks::selectValve1));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V2"), &MenuCallbacks::selectValve2));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V3"), &MenuCallbacks::selectValve3));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V4"), &MenuCallbacks::selectValve4));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V5"), &MenuCallbacks::selectValve5));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V6"), &MenuCallbacks::selectValve6));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V7"), &MenuCallbacks::selectValve7));
//    settingsValvesMenu->addSubItem(new CallableMenu(F("V8"), &MenuCallbacks::selectValve8));
//
//    settingsSystemMenu->addSubItem(new CallableMenu(F("Date"), &MenuCallbacks::setDate));
//    settingsSystemMenu->addSubItem(new CallableMenu(F("Time"), &MenuCallbacks::setTime));
//    settingsSystemMenu->addSubItem(new CallableMenu(F("Save Settings"), &MenuCallbacks::saveSettings));
//    settingsSystemMenu->addSubItem(new CallableMenu(F("Load Settings"), &MenuCallbacks::loadSettings));
//    settingsSystemMenu->addSubItem(new CallableMenu(F("Factory Reset"), &MenuCallbacks::resetToFactorySettings));
//
//    ShowNextIrrigationMenu::createInstance(infoMenu);
//    infoMenu->addSubItem(new CallableMenu(F("DataTime"), &MenuCallbacks::showDataTime));
//    infoMenu->addSubItem(new CallableMenu(F("Next Irrigation"), &MenuCallbacks::setShowNextIrrigationMenu));
//
//    // Create the menu instance
//    Menu::createInstance(mainMenu);
//  }