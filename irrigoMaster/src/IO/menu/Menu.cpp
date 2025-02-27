#include "menu.h"
#include "Debug.hpp"
#include "MenuValve.h"
#include "../IOSystem.h"

Menu::Menu(LCD *lcd, RotaryEncoder *rotaryEncoder, IOSystem *iosys)
    : lcd(lcd),
      rotaryEncoder(rotaryEncoder),
      iosys(iosys),
      cursor(0),
      currentItem(nullptr)
{
    currentItem = Menu::create(iosys);
    print();
}

void Menu::update()
{
    Command cmd = rotaryEncoder->readCommand();

    if (cmd == Command::NONE && currentItem->getRefresh(false) == RefreshType::NONE)
        return;

    else if (cmd == Command::RIGHT && currentItem->exeRightCmd())
    {
        cursor++;
    }
    else if (cmd == Command::LEFT && currentItem->exeLeftCmd())
    {
        cursor--;
    }
    else if (cmd == Command::SELECT && currentItem->exeSelectCmd(currentItem))
    {
        cursor = 0;
    }

    print();
}

void Menu::print()
{
    RefreshType refresType = currentItem->getRefresh();

    if (cursor < 0)
    {
        cursor = 0;
        refresType = RefreshType::CLEAR_ALL;
    }
    else if (cursor >= lcd->getLinesNumber())
    {
        cursor = lcd->getLinesNumber() - 1;
        refresType = RefreshType::CLEAR_ALL;
    }

    if (refresType != RefreshType::NONE)
    {
        if (refresType == RefreshType::CLEAR_ALL)
        {
            lcd->clear();
        }

        for (uint8_t line = 0; line < lcd->getLinesNumber(); line++)
        {
            if (currentItem->printLine(lcd, line, (uint8_t)cursor) == false)
                break;
        }
    }
    else
    {
        lcd->clearColumn(0);
    }

    printCursor();
}

void Menu::printCursor()
{
    lcd->print(">", 0, cursor);
}

MenuList *Menu::create(IOSystem *iosys)
{
    MenuList *mainMenu = new MenuList(F("Main"), 2);
    MenuList *settingsMenu = new MenuList(F("Settings"), 1);
    MenuList *infoMenu = new MenuList(F("Info"), 1, false);

    mainMenu->addItem(settingsMenu);
    mainMenu->addItem(infoMenu);

    MenuValve *menuValve = new MenuValve(F("Valve settings"), iosys);

    settingsMenu->addItem(menuValve);
    infoMenu->addItem(menuValve);

    return mainMenu; // Return the top-level menu
}