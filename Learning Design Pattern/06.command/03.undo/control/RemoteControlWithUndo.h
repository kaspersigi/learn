#pragma once
#include "../interface/Command.h"
#include <array>
#include <memory>
#include <string>

class RemoteControlWithUndo {
public:
    RemoteControlWithUndo();
    ~RemoteControlWithUndo() = default;

    void setCommand(int slot, Command* onCommand, Command* offCommand);
    void onButtonWasPushed(int slot) const;
    void offButtonWasPushed(int slot) const;
    void undoButtonWasPushed() const;
    std::string toShow() const;

protected:
    RemoteControlWithUndo(const RemoteControlWithUndo&) = delete;
    RemoteControlWithUndo(RemoteControlWithUndo&&) = delete;
    RemoteControlWithUndo& operator=(const RemoteControlWithUndo&) = delete;
    RemoteControlWithUndo& operator=(RemoteControlWithUndo&&) = delete;

private:
    static const int SLOTS = 7;
    mutable std::shared_ptr<Command> _undoCommand {};
    std::array<std::shared_ptr<Command>, SLOTS> _onCommands {};
    std::array<std::shared_ptr<Command>, SLOTS> _offCommands {};
};