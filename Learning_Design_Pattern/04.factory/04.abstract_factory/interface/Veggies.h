#pragma once

#include "NonCopyable.h"
#include <string>

class Veggies : public NonCopyable {
public:
    virtual ~Veggies() = default;

    virtual std::string toShow() const = 0;

protected:
    Veggies() = default;
};