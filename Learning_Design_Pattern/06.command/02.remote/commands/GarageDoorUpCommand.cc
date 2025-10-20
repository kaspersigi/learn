#include "GarageDoorUpCommand.h"
#include <iostream>

GarageDoorUpCommand::GarageDoorUpCommand(const std::shared_ptr<const GarageDoor>& garageDoor)
    : _garageDoor(garageDoor)
{
}

GarageDoorUpCommand::~GarageDoorUpCommand() = default;

void GarageDoorUpCommand::execute() const
{
    if (_garageDoor.use_count())
        _garageDoor.lock()->up();
    else
        std::cout << "device is broken" << std::endl;
}