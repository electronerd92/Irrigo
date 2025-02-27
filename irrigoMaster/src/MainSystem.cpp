#include "MainSystem.h"
#include "ProjectConfig.h"
#include "IO/IOSystem.h"
#include "Irrigation/IrrigationSystem.h"

MainSystem::MainSystem()
    : rtc()
{
    rtc.begin();
    irrigationSystem = new IrrigationSystem(this); // first this because ioSystem need it
    ioSystem = new IOSystem(this);
}

void MainSystem::update()
{
    ioSystem->update();
}

IrrigationSystem *MainSystem::getIrrigationSystem()
{
    return irrigationSystem;
}