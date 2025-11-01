#pragma once

#include "NonCopyable.h"
#include <string>

class Cheese : public NonCopyable {
public:
    virtual ~Cheese() = default;

    virtual std::string toShow() const = 0;

protected:
    Cheese() = default;
};