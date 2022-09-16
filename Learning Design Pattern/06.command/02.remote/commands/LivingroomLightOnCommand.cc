#include "LivingroomLightOnCommand.h"

LivingroomLightOnCommand::LivingroomLightOnCommand(const Light* light)
{
    _light = std::shared_ptr<const Light>(light);
}

void LivingroomLightOnCommand::execute() const
{
    _light->on();
}