#include "LightOffCommand.h"
#include <iostream>

LightOffCommand::LightOffCommand(std::shared_ptr<const Light> light)
    : _light(light)
{
}

void LightOffCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}