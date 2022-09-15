#include "GarageDoorDownCommand.h"

GarageDoorDownCommand::GarageDoorDownCommand(const GarageDoor* garageDoor)
{
    _garageDoor = std::shared_ptr<const GarageDoor>(garageDoor);
}

void GarageDoorDownCommand::execute() const
{
    _garageDoor->down();
}