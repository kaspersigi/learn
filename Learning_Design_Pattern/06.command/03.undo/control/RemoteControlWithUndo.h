#pragma once

#include "../interface/NonCopyable.h"
#include <array>
#include <memory>
#include <string>

class Command;

class RemoteControlWithUndo : public NonCopyable {
public:
    RemoteControlWithUndo();
    ~RemoteControlWithUndo();

    void setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand);
    void onButtonWasPushed(int slot) const;
    void offButtonWasPushed(int slot) const;
    void undoButtonWasPushed() const;
    std::string toShow() const;

private:
    static const int SLOTS = 7;
    mutable std::shared_ptr<Command> _undoCommand;
    std::array<std::shared_ptr<Command>, SLOTS> _onCommands;
    std::array<std::shared_ptr<Command>, SLOTS> _offCommands;
};