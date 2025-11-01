#pragma once

#include "NonCopyable.h"
#include <string>

class Sauce : public NonCopyable {
public:
    virtual ~Sauce() = default;

    virtual std::string toShow() const = 0;

protected:
    Sauce() = default;
};