#pragma once

#include "NonCopyable.h"

class Command : public NonCopyable {
public:
    virtual ~Command() = default;
    virtual void execute() const = 0;

protected:
    Command() = default;
};