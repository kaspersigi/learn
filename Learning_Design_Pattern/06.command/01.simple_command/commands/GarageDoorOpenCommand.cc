#include "GarageDoorOpenCommand.h"
#include <iostream>

GarageDoorOpenCommand::GarageDoorOpenCommand(const std::shared_ptr<const GarageDoor>& garageDoor)
    : _garageDoor(garageDoor)
{
}

GarageDoorOpenCommand::~GarageDoorOpenCommand() = default;

void GarageDoorOpenCommand::execute() const
{
    if (_garageDoor.use_count())
        _garageDoor.lock()->up();
    else
        std::cout << "device is broken" << std::endl;
}