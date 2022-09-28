#pragma once
#include "../interface/Command.h"
#include <memory>

class NoCommand : public Command {
public:
    NoCommand() = default;
    virtual ~NoCommand() = default;

    void execute() const override;

protected:
    NoCommand(const NoCommand&) = delete;
    NoCommand(NoCommand&&) = delete;
    NoCommand& operator=(const NoCommand&) = delete;
    NoCommand& operator=(NoCommand&&) = delete;
};