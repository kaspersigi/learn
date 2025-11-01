#pragma once

#include "NonCopyable.h"

class QuackBehavior : public NonCopyable {
public:
    virtual ~QuackBehavior() = default;

    virtual void quack() const = 0;

protected:
    QuackBehavior() = default;
};