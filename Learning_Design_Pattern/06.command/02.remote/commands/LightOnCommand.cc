#include "LightOnCommand.h"
#include <iostream>

LightOnCommand::LightOnCommand(const std::shared_ptr<const Light>& light)
    : _light(light)
{
}

LightOnCommand::~LightOnCommand() = default;

void LightOnCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->on();
    else
        std::cout << "device is broken" << std::endl;
}