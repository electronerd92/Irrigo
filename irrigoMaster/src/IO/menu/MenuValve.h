#ifndef MENU_VALVE_H
#define MENU_VALVE_H

#include <Arduino.h>
#include "MenuNode.h"
#include "../IOSystem.h"

class MenuValve : public MenuNode
{
public:
    struct NodeItem
    {
        const __FlashStringHelper *name;
        uint8_t subItems;
        const char *(MenuValve::*getter)();
        void (MenuValve::*setter)(bool);
    };

private:
    static const uint8_t NODE_ITEMS_COUNT = 5;
    NodeItem valveSettings[NODE_ITEMS_COUNT];
    uint8_t currentSubIndex;

    const char *getValveIndex();
    void setValveIndex(bool goUp);
    const char *getStartTime();
    void setStartTime(bool goUp);
    const char *getMode();
    void setMode(bool goUp);
    const char *getFrequency();
    void setFrequency(bool goUp);
    const char *getDuration();
    void setDuration(bool goUp);

public:
    MenuValve(const __FlashStringHelper *name, IOSystem *iosys);

    void customExtraInit() override;
    uint8_t getItemsCount() override;
    bool customExeRightCmd() override;
    bool customExeLeftCmd() override;
    bool customExeSelectCmd(MenuItem *&currentMenuItem) override;
    bool customPrintLine(LCD *lcd, uint8_t line, uint8_t index) override;
};

#endif // MENU_VALVE_H