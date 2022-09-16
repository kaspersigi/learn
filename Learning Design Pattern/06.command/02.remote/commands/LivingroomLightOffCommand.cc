#include "LivingroomLightOffCommand.h"

LivingroomLightOffCommand::LivingroomLightOffCommand(const Light* light)
{
    _light = std::shared_ptr<const Light>(light);
}

void LivingroomLightOffCommand::execute() const
{
    _light->off();
}