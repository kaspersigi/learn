#include "RemoteControl.h"
#include "../commands/NoCommand.h"
#include <algorithm>
#include <cassert>

RemoteControl::RemoteControl()
{
    std::for_each(_offCommands.begin(), _offCommands.end(), [](auto& e) { e = std::make_shared<NoCommand>(); });
    std::for_each(_onCommands.begin(), _onCommands.end(), [](auto& e) { e = std::make_shared<NoCommand>(); });
}

void RemoteControl::setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
{
    assert(slot <= SLOTS);
    _onCommands[slot] = onCommand;
    _offCommands[slot] = offCommand;
}

void RemoteControl::onButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    _onCommands[slot]->execute();
}

void RemoteControl::offButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    _offCommands[slot]->execute();
}

std::string RemoteControl::toShow() const
{
    std::string value;
    value += "------ Remote Control -------\n";
    for (int i = 0; i < SLOTS; ++i) {
        value += "[slot " + std::to_string(i) + "] ";
        value += typeid(*_onCommands[i]).name();
        value += "    ";
        value += typeid(*_offCommands[i]).name();
        value += "\n";
    }
    return value;
}