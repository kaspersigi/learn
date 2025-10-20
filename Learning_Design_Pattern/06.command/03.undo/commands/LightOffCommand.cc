#include "LightOffCommand.h"
#include <iostream>

LightOffCommand::LightOffCommand(const std::shared_ptr<const Light>& light)
    : _light(light)
{
}

LightOffCommand::~LightOffCommand() = default;

void LightOffCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}

void LightOffCommand::undo() const
{
    if (_light.use_count())
        _light.lock()->on();
    else
        std::cout << "device is broken" << std::endl;
}