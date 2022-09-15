#include "GarageDoorOpenCommand.h"

GarageDoorOpenCommand::GarageDoorOpenCommand(const GarageDoor* garageDoor)
{
    _garageDoor = std::shared_ptr<const GarageDoor>(garageDoor);
}

void GarageDoorOpenCommand::execute() const
{
    _garageDoor->up();
}