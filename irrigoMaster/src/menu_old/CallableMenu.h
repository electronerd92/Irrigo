#ifndef CALLABLEMENU_H
#define CALLABLEMENU_H

#include "MenuObject.h"

class CallableMenu : public MenuObject
{
private:
    const __FlashStringHelper *name;
    bool (*callback)(Command);

public:
    CallableMenu(const __FlashStringHelper *name, bool (*callback)(Command));
    MenuObjectType getType() const override
    {
        return MenuObjectType::CALLABLE;
    }
    const __FlashStringHelper *getName() const override;
    bool selectEffect(Command cmd) const override;
};

#endif // CALLABLEMENU_H