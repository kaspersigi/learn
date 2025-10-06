#pragma once

#include "../../interface/Cheese.h"
#include <string>

class ReggianoCheese : public Cheese
{
public:
    ReggianoCheese() = default;
    virtual ~ReggianoCheese() = default;

    virtual std::string toShow() const override;
};