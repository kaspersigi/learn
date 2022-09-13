#include "LightOffCommand.h"

LightOffCommand::LightOffCommand(const Light* light)
{
    _light = std::shared_ptr<const Light>(light);
}

void LightOffCommand::execute() const
{
    _light->off();
}