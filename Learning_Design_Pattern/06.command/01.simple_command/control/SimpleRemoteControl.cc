#include "SimpleRemoteControl.h"
#include <cassert>

void SimpleRemoteControl::setCommand(std::shared_ptr<const Command> command)
{
    assert(command);
    _slot = command;
}

void SimpleRemoteControl::buttonWasPressed() const
{
    assert(_slot);
    _slot->execute();
}