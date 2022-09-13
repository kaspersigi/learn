#include "LightOnCommand.h"

LightOnCommand::LightOnCommand(const Light* light)
{
    _light = std::shared_ptr<const Light>(light);
}

void LightOnCommand::execute() const
{
    _light->on();
}