#include "MainSystem.h"
#include "ProjectConfig.h"
#include "IOSystem.h"

MainSystem::MainSystem()
    : rtc()
{
    rtc.begin();
    ioSystem = new IOSystem(this);
}

void MainSystem::update()
{
}