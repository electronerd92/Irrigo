#ifndef MENNU_EDITABLE_H
#define MENNU_EDITABLE_H

#include <Arduino.h>
#include "MenuItem.h"
#include "../../IOSystem.h"

class MenuEdit : public MenuItem
{
private:
    bool canEdit;
    IOSystem *ioSystem;

public:
    explicit MenuEdit(const __FlashStringHelper *name, IOSystem *iosys) : MenuItem(name), ioSystem(iosys) {};
}

class MenuEditWrapper : public MenuEdit
{
private:
    MenuEdit *source;

public:
    explicit MenuEditWrapper(MenuEdit * src, bool canEdt ) : source(src), canEdit(canEdt) {};
    
}

#endif // MENNU_EDITABLE_H