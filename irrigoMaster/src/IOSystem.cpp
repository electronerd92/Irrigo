#include "IOSystem.h"
#include "ProjectConfig.h"

IOSystem::IOSystem(MainSystem *mainSystem)
    : mainSystem(mainSystem),
      lcd(),
      rotaryEncoder(),
      menu(&lcd, &rotaryEncoder)
{
}

void IOSystem::update()
{
  rotaryEncoder.update();
}