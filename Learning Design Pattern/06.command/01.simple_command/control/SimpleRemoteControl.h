#pragma once
#include "../interface/Command.h"
#include <memory>

class SimpleRemoteControl {
public:
    SimpleRemoteControl() = default;
    virtual ~SimpleRemoteControl() = default;

    void setCommand(const Command* command);
    void buttonWasPressed() const;

protected:
    SimpleRemoteControl(const SimpleRemoteControl&) = delete;
    SimpleRemoteControl(SimpleRemoteControl&&) = delete;
    SimpleRemoteControl& operator=(const SimpleRemoteControl&) = delete;
    SimpleRemoteControl& operator=(SimpleRemoteControl&&) = delete;

private:
    std::shared_ptr<const Command> _slot {};
};