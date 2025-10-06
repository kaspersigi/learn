#include "RemoteControlWithUndo.h"
#include "../commands/NoCommand.h"
#include <algorithm>
#include <cassert>

RemoteControlWithUndo::RemoteControlWithUndo()
{
    _undoCommand = std::make_shared<NoCommand>();
    std::for_each(_offCommands.begin(), _offCommands.end(), [](auto& e) { e = std::make_shared<NoCommand>(); });
    std::for_each(_onCommands.begin(), _onCommands.end(), [](auto& e) { e = std::make_shared<NoCommand>(); });
}

void RemoteControlWithUndo::setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
{
    assert(slot <= SLOTS);
    _onCommands[slot] = onCommand;
    _offCommands[slot] = offCommand;
}

void RemoteControlWithUndo::onButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    if (dynamic_cast<NoCommand*>(_onCommands[slot].get()) == nullptr) {
        _onCommands[slot]->execute();
        _undoCommand = _onCommands[slot];
    } else {
        _onCommands[slot]->execute();
    }
}

void RemoteControlWithUndo::offButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    if (dynamic_cast<NoCommand*>(_offCommands[slot].get()) == nullptr) {
        _offCommands[slot]->execute();
        _undoCommand = _offCommands[slot];
    } else {
        _offCommands[slot]->execute();
    }
}

void RemoteControlWithUndo::undoButtonWasPushed() const { _undoCommand->undo(); }

std::string RemoteControlWithUndo::toShow() const
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
    value += "[undo] ";
    value += typeid(*_undoCommand).name();
    value += "\n";
    return value;
}