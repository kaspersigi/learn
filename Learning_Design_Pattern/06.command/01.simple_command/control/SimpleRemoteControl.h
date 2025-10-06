#pragma once
#include "../interface/Command.h"
#include "../interface/NonCopyable.h"
#include <memory>

class SimpleRemoteControl : public NonCopyable
{
public:
    SimpleRemoteControl() = default;
    virtual ~SimpleRemoteControl() = default;

    void setCommand(std::shared_ptr<const Command> command);
    void buttonWasPressed() const;

private:
    std::shared_ptr<const Command> _slot {};
};