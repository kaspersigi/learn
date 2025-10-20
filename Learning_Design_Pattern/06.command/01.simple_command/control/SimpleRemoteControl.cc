#include "SimpleRemoteControl.h"
#include "../interface/Command.h"

SimpleRemoteControl::SimpleRemoteControl() = default;
SimpleRemoteControl::~SimpleRemoteControl() = default;

void SimpleRemoteControl::setCommand(const std::shared_ptr<const Command>& command)
{
    _slot = command;
}

void SimpleRemoteControl::buttonWasPressed() const
{
    _slot->execute();
}