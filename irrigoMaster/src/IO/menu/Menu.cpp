#include "menu.h"
#include "Debug.hpp"
#include "MenuIterableItem.h"

Menu::Menu(LCD *lcd, RotaryEncoder *rotaryEncoder)
{
    this->lcd = lcd;
    this->rotaryEncoder = rotaryEncoder;

    create();
}

void Menu::create()
{
    MenuIterableItem *mainMenu = new MenuIterableItem(F("Main"), 2);
    MenuIterableItem *settingsMenu = new MenuIterableItem(F("Settings"), 2);
    MenuIterableItem *infoMenu = new MenuIterableItem(F("Info"), 2);

    mainMenu->addItem(settingsMenu);
    mainMenu->addItem(infoMenu);
}

void Menu::update()
{
    Command cmd = rotaryEncoder->readCommand();

    if (currentItem->getType() == MenuItemType::ITERABLE)
    {
        MenuIterableItem *currentIterableItem = static_cast<MenuIterableItem *>(currentItem);

        if (cmd == Command::DOWN)
        {
            currentIterableItem->increaseIndex();
        }
        else if (cmd == Command::UP)
        {
            currentIterableItem->decreaseIndex();
        }
        else if (cmd == Command::SELECT)
        {
            currentItem = currentIterableItem->selectItem();
        }
    }
}

void Menu::print()
{
    for (uint8_t line = 0; line < lcd->getLinesNumber(); line++)
    {
        
    }
}