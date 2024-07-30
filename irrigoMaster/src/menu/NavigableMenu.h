#ifndef NAVIGABLEMENU_H
#define NAVIGABLEMENU_H

#include <Arduino.h>
#include "MenuObject.h"
#include "MenuIterableObject.h"
#include "Command.h"
#include "LCDManager.h"

class NavigableMenu : public MenuIterableObject
{
private:
    const __FlashStringHelper *name;
    MenuObject **subItems;
    uint8_t subItemCount;
    const uint8_t maxSubItems;
    uint8_t selectedIndex;

public:
    NavigableMenu(const __FlashStringHelper *name, uint8_t maxSubItems);

    bool addSubItem(MenuObject *item);

    const __FlashStringHelper *getName() const override;

    const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const override;

    uint8_t getSelectedIndex() const override;

    void resetSelectedIndex() override;

    bool incrementSelectedIndex() override;

    bool decrementSelectedIndex() override;

    bool select(Command cmd) const override;

    bool selectEffect(Command cmd) const override;

    void setParent(MenuIterableObject *parent) override;

    MenuIterableObject *getParent() const override;

    void removeParent();
};

#endif // NAVIGABLEMENU_H