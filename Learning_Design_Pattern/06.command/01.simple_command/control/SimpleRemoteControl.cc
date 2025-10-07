#include "SimpleRemoteControl.h"
#include "../interface/Command.h"
#include <cassert>

SimpleRemoteControl::SimpleRemoteControl() = default;
SimpleRemoteControl::~SimpleRemoteControl() = default;

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