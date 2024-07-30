#ifndef VALVESETTINGSMENU_H
#define VALVESETTINGSMENU_H

#include "NavigableMenu.h"
#include "../irrigationSystem/Valve.h"
#include "Command.h"
#include "LCDManager.h"

class ValveSettingsMenu : public MenuIterableObject
{
private:
    static ValveSettingsMenu *instance;
    NavigableMenu *parent;
    Valve *source;   // Pointer to the original Valve object
    Valve tmpSource; // Copy of the Valve object for modifications

    uint8_t selectedIndex;

    uint8_t timeModeCount;
    const __FlashStringHelper **timeModeSettings;
    // const __FlashStringHelper **autoModeSettings;
    // uint8_t autoModeCount;

    // Private constructor to prevent external instantiation
    ValveSettingsMenu();

    void create();

public:
    // Deleted copy constructor and assignment operator to prevent copies
    ValveSettingsMenu(const ValveSettingsMenu &) = delete;
    ValveSettingsMenu &operator=(const ValveSettingsMenu &) = delete;

    // Static method to get the singleton instance
    static ValveSettingsMenu &getInstance();

    void setSource(Valve *source);

    // Implement abstract methods from MenuIterableObject
    bool selectEffect(Command cmd) const override;
    const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const override;
    uint8_t getSelectedIndex() const override;
    void resetSelectedIndex() override;
    bool incrementSelectedIndex() override;
    bool decrementSelectedIndex() override;
    bool select(Command cmd) const override;
    const __FlashStringHelper *getName() const override { return nullptr; };
    MenuIterableObject *getParent() const override;
    void setParent(MenuIterableObject *parent) override;
};

#endif // VALVESETTINGSMENU_H