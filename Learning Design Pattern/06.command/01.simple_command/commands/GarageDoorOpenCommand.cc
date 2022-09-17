#include "GarageDoorOpenCommand.h"
#include <iostream>

GarageDoorOpenCommand::GarageDoorOpenCommand(std::shared_ptr<const GarageDoor> garageDoor)
    : _garageDoor(garageDoor)
{
}

void GarageDoorOpenCommand::execute() const
{
    if (_garageDoor.use_count())
        _garageDoor.lock()->up();
    else
        std::cout << "device is broken" << std::endl;
}