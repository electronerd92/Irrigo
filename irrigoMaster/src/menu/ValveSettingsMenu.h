#ifndef VALVESETTINGSMENU_H
#define VALVESETTINGSMENU_H

#include "MenuIterableObject.h"
#include "CallableMenu.h"
#include "../irrigationSystem/Valve.h"
#include "Command.h"
#include "LCDManager.h"

class ValveSettingsMenu : public MenuIterableObject
{
private:
    static ValveSettingsMenu *instance;
    MenuIterableObject *parent;
    Valve *source;   // Pointer to the original Valve object
    Valve tmpSource; // Copy of the Valve object for modifications

    uint8_t selectedIndex;

    const CallableMenu *goBackMenu;
    const CallableMenu *validateSettingsMenu;

    const CallableMenu *changeModeMenu;

    const CallableMenu *setStartTimeMenu;
    const CallableMenu *setDurationMenu;
    const CallableMenu *setFrequencyMenu;
    const CallableMenu *setSoilMoistureLevelMenu;

    // Private constructor to prevent external instantiation
    ValveSettingsMenu();

    const uint8_t getMaxCount() const;
    const CallableMenu *getSelectedMenu() const;

    static bool initialActionPerformed; // Static variable to track state

    // Static callback functions
    static bool goBack(Command cmd);
    static bool validateSettings(Command cmd);
    static bool changeMode(Command cmd);
    static bool setStartTime(Command cmd);
    static bool setDuration(Command cmd);
    static bool setFrequency(Command cmd);
    static bool setSoilMoistureLevel(Command cmd);

public:
    // Deleted copy constructor and assignment operator to prevent copies
    ValveSettingsMenu(const ValveSettingsMenu &) = delete;
    ValveSettingsMenu &operator=(const ValveSettingsMenu &) = delete;

    // Static method to get the singleton instance
    static ValveSettingsMenu &getInstance();

    void setSource(Valve *source);

    // Getter for tmpSource
    static Valve &getTmpSource();

    void validateTmpSource();

    // Implement abstract methods from MenuIterableObject
    const __FlashStringHelper *getName() const override { return nullptr; };
    bool selectEffect(Command cmd) const override { return false; };
    const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const override;
    uint8_t getSelectedIndex() const override;
    void resetSelectedIndex() override;
    bool incrementSelectedIndex() override;
    bool decrementSelectedIndex() override;
    bool select(Command cmd) const override;
    MenuIterableObject *getParent() const override;
    void setParent(MenuIterableObject *parent) override;
};

#endif // VALVESETTINGSMENU_H