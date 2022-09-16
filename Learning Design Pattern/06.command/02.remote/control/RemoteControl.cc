#include "RemoteControl.h"
#include <cassert>

void RemoteControl::setCommand(const Command* command)
{
    assert(command);
    _slot = std::shared_ptr<const Command>(command);
}

void RemoteControl::buttonWasPressed() const
{
    assert(_slot);
    _slot->execute();
}