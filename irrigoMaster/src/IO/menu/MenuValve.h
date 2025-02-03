#ifndef MENU_VALVE_H
#define MENU_VALVE_H

#include <Arduino.h>
#include "MenuNode.h"
#include "../../IOSystem.h"

class MenuValve : public MenuNode
{
public:
    struct NodeItem
    {
        const __FlashStringHelper *name;
        const char *(MenuValve::*getter)();
        void (MenuValve::*setter)(IncreaseDecrease);
    };

private:
    static constexpr uint8_t nodeItemsCount = 1;
    NodeItem valveSettings[nodeItemsCount];

    const char *getValveState();
    void setValveState(IncreaseDecrease action);

public:
    MenuValve(const __FlashStringHelper *name, IOSystem *iosys);

    uint8_t getItemsCount() override;
    bool customExeRightCmd() override;
    bool customExeLeftCmd() override;
    bool customExeSelectCmd(MenuItem *&currentMenuItem) override;
    bool customPrintLine(LCD *lcd, uint8_t line, uint8_t index) override;
};

#endif // MENU_VALVE_H