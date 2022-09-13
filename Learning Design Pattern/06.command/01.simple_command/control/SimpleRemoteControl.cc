#include "SimpleRemoteControl.h"
#include <cassert>

void SimpleRemoteControl::setCommand(const Command* command)
{
    assert(command);
    _slot = std::shared_ptr<const Command>(command);
}

void SimpleRemoteControl::buttonWasPressed() const
{
    assert(_slot);
    _slot->execute();
}