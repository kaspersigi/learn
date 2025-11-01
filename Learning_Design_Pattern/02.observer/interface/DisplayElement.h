#pragma once

#include "NonCopyable.h"

class DisplayElement : public NonCopyable {
public:
    virtual ~DisplayElement() = default;

    virtual void display() const = 0;

protected:
    DisplayElement() = default;
};