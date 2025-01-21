#include "menu.h"
#include "Debug.hpp"

Menu::Menu(LCD *lcd, RotaryEncoder *rotaryEncoder)
    : lcd(lcd), rotaryEncoder(rotaryEncoder), cursor(0), currentItem(nullptr)
{
    currentItem = Menu::create();
}

void Menu::update()
{
    Command cmd = rotaryEncoder->readCommand();

    if (currentItem->getType() == MenuItemType::ITERABLE)
    {
        MenuIterableItem *currentIterableItem = static_cast<MenuIterableItem *>(currentItem);

        if (cmd == Command::DOWN && currentIterableItem->increaseCurrentIndex())
        {
            cursor++;
        }
        else if (cmd == Command::UP && currentIterableItem->decreaseCurrentIndex())
        {
            cursor--;
        }
        else if (cmd == Command::SELECT)
        {
            currentItem = currentIterableItem->selectItem();
        }
    }
}

void Menu::printIterableMenu(MenuIterableItem *menuIterableItem)
{
    bool refreshAll = false;

    if (cursor < 0)
    {
        cursor = 0;
        refreshAll = true;
    }
    else if (cursor >= lcd->getLinesNumber())
    {
        cursor = (int)(lcd->getLinesNumber()) - 1;
        refreshAll = true;
    }

    if (refreshAll)
    {
        lcd->clear();
        uint8_t offset = menuIterableItem->getCurrentIndex() - cursor;

        for (uint8_t line = 0; line < lcd->getLinesNumber(); line++)
        {
            if (menuIterableItem->printContentAtIndex(offset + line, lcd, line) == false)
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


MenuIterableItem* Menu::create()
{
    MenuIterableItem* mainMenu = new MenuIterableItem(F("Main"), 2);
    MenuIterableItem* settingsMenu = new MenuIterableItem(F("Settings"), 2);
    MenuIterableItem* infoMenu = new MenuIterableItem(F("Info"), 2);

    mainMenu->addItem(settingsMenu);
    mainMenu->addItem(infoMenu);

    return mainMenu; // Return the top-level menu
}