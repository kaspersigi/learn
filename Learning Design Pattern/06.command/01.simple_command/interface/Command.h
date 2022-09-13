#pragma once

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;

protected:
    Command() = default;
    Command(const Command&) = delete;
    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;
};