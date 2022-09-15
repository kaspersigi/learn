#include "GarageDoorUpCommand.h"

GarageDoorUpCommand::GarageDoorUpCommand(const GarageDoor* garageDoor)
{
    _garageDoor = std::shared_ptr<const GarageDoor>(garageDoor);
}

void GarageDoorUpCommand::execute() const
{
    _garageDoor->up();
}