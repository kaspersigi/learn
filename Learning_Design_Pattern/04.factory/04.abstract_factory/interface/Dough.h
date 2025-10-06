#pragma once

#include "NonCopyable.h"
#include <string>

class Dough
{
public:
    virtual ~Dough() = default;

    virtual std::string toShow() const = 0;

protected:
    Dough() = default;
};