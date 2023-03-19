#include "LightOnCommand.h"
#include <iostream>

LightOnCommand::LightOnCommand(std::shared_ptr<const Light> light)
    : _light(light)
{
}

void LightOnCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->on();
    else
        std::cout << "device is broken" << std::endl;
}

void LightOnCommand::undo() const
{
    if (_light.use_count())
        _light.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}