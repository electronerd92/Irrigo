#include "System.h"

// Initialize the static member
System *System::instance = nullptr;

System::System()
{
    rtc.begin();
}

System &System::getInstance()
{
    if (instance == nullptr)
    {
        instance = new System();
    }
    return *instance;
}

uint32_t System::getUnixTime()
{
    return rtc.now().unixtime();
}