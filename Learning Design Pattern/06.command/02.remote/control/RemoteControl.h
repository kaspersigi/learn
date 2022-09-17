#pragma once
#include "../interface/Command.h"
#include <array>
#include <memory>
#include <string>

class RemoteControl {
public:
    RemoteControl();
    ~RemoteControl() = default;

    void setCommand(int slot, Command* onCommand, Command* offCommand);
    void onButtonWasPushed(int slot) const;
    void offButtonWasPushed(int slot) const;
    std::string toShow() const;

protected:
    RemoteControl(const RemoteControl&) = delete;
    RemoteControl(RemoteControl&&) = delete;
    RemoteControl& operator=(const RemoteControl&) = delete;
    RemoteControl& operator=(RemoteControl&&) = delete;

private:
    static const int SLOTS = 7;
    std::array<std::shared_ptr<Command>, SLOTS> _onCommands {};
    std::array<std::shared_ptr<Command>, SLOTS> _offCommands {};
};