#include "GarageDoorDownCommand.h"
#include <iostream>

GarageDoorDownCommand::GarageDoorDownCommand(std::shared_ptr<const GarageDoor> garageDoor)
    : _garageDoor(garageDoor)
{
}

void GarageDoorDownCommand::execute() const
{
    if (_garageDoor.use_count())
        _garageDoor.lock()->down();
    else
        std::cout << "device is broken" << std::endl;
}