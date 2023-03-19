#include "LivingroomLightOffCommand.h"
#include <iostream>

LivingroomLightOffCommand::LivingroomLightOffCommand(std::shared_ptr<const Light> light)
    : _light(light)
{
}

void LivingroomLightOffCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}