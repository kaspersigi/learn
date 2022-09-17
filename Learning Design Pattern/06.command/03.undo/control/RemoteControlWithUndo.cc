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

void RemoteControlWithUndo::setCommand(int slot, Command* onCommand, Command* offCommand)
{
    assert(slot <= SLOTS);
    assert(onCommand);
    assert(offCommand);
    _onCommands[slot] = std::shared_ptr<Command>(onCommand);
    _offCommands[slot] = std::shared_ptr<Command>(offCommand);
}

void RemoteControlWithUndo::onButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    _onCommands[slot]->execute();
    _undoCommand = _onCommands[slot];
}

void RemoteControlWithUndo::offButtonWasPushed(int slot) const
{
    assert(slot <= SLOTS);
    _offCommands[slot]->execute();
    _undoCommand = _offCommands[slot];
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