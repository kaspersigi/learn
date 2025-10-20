#include "LivingroomLightOnCommand.h"
#include <iostream>

LivingroomLightOnCommand::LivingroomLightOnCommand(const std::shared_ptr<const Light>& light)
    : _light(light)
{
}

LivingroomLightOnCommand::~LivingroomLightOnCommand() = default;

void LivingroomLightOnCommand::execute() const
{
    if (_light.use_count())
        _light.lock()->on();
    else
        std::cout << "device is broken" << std::endl;
}