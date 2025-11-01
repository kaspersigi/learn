#pragma once

#include "../interface/NonCopyable.h"
#include <array>
#include <memory>
#include <string>

class Command;

class RemoteControl : public NonCopyable {
public:
    RemoteControl();
    virtual ~RemoteControl();

    void setCommand(int slot, std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand);
    void onButtonWasPushed(int slot) const;
    void offButtonWasPushed(int slot) const;
    std::string toShow() const;

private:
    static const int SLOTS = 7;
    std::array<std::shared_ptr<Command>, SLOTS> _onCommands;
    std::array<std::shared_ptr<Command>, SLOTS> _offCommands;
};