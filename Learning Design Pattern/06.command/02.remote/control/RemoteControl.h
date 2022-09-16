#pragma once
#include "../interface/Command.h"
#include <memory>

class RemoteControl {
public:
    RemoteControl() = default;
    ~RemoteControl() = default;

    void setCommand(const Command* command);
    void buttonWasPressed() const;

protected:
    RemoteControl(const RemoteControl&) = delete;
    RemoteControl(RemoteControl&&) = delete;
    RemoteControl& operator=(const RemoteControl&) = delete;
    RemoteControl& operator=(RemoteControl&&) = delete;

private:
    std::shared_ptr<const Command> _slot;
};