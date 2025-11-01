#pragma once
#include "../interface/Command.h"
#include <memory>

class NoCommand : public Command {
public:
    NoCommand() = default;
    virtual ~NoCommand() = default;

    void execute() const override;
    void undo() const override;
};