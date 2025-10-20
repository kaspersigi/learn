#include "GarageDoorDownCommand.h"
#include <iostream>

GarageDoorDownCommand::GarageDoorDownCommand(const std::shared_ptr<const GarageDoor>& garageDoor)
    : _garageDoor(garageDoor)
{
}

GarageDoorDownCommand::~GarageDoorDownCommand() = default;

void GarageDoorDownCommand::execute() const
{
    if (_garageDoor.use_count())
        _garageDoor.lock()->down();
    else
        std::cout << "device is broken" << std::endl;
}