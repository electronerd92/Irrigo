#ifndef SHOWNEXTIRRIGATIONMENU_H
#define SHOWNEXTIRRIGATIONMENU_H

#include "MenuIterableObject.h"
#include "LCDManager.h"

class ShowNextIrrigationMenu : public MenuIterableObject
{
private:
    static ShowNextIrrigationMenu *instance;
    MenuIterableObject *parent;
    uint8_t selectedIndex;

    // Private constructor to prevent external instantiation
    ShowNextIrrigationMenu(MenuIterableObject *parent);

public:
    // Deleted copy constructor and assignment operator to prevent copies
    ShowNextIrrigationMenu(const ShowNextIrrigationMenu &) = delete;
    ShowNextIrrigationMenu &operator=(const ShowNextIrrigationMenu &) = delete;

    // Static method to create the singleton instance
    static void createInstance(MenuIterableObject *parent);

    // Static method to get the singleton instance
    static ShowNextIrrigationMenu &getInstance();

    // Implement abstract methods from MenuIterableObject
    const __FlashStringHelper *getName() const override { return nullptr; };
    bool selectEffect(Command cmd) const override { return false; };
    void setParent(MenuIterableObject *parent) override {};
    MenuIterableObject *getParent() const override { return nullptr; };
    const bool printContentAtIndex(uint8_t index, LCDManager &lcdManager, uint8_t row) const override;
    uint8_t getSelectedIndex() const override;
    void setSelectedIndex(uint8_t index) override;
    bool incrementSelectedIndex() override;
    bool decrementSelectedIndex() override;
    bool select(Command cmd) const override;
};
#endif // SHOWNEXTIRRIGATIONMENU_H