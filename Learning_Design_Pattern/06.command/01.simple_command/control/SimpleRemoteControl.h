#pragma once
#include "../interface/NonCopyable.h"
#include <memory>

class Command;

class SimpleRemoteControl : public NonCopyable
{
public:
    SimpleRemoteControl();
    ~SimpleRemoteControl();

    void setCommand(std::shared_ptr<const Command> command);
    void buttonWasPressed() const;

private:
    std::shared_ptr<const Command> _slot;
};