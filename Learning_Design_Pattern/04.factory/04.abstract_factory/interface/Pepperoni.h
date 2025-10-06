#pragma once

#include "NonCopyable.h"
#include <string>

class Pepperoni : public NonCopyable
{
public:
    virtual ~Pepperoni() = default;

    virtual std::string toShow() const = 0;

protected:
    Pepperoni() = default;
};