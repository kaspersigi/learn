#pragma once

#include "../../interface/Pepperoni.h"
#include <string>

class SlicedPepperoni : public Pepperoni
{
public:
    SlicedPepperoni() = default;
    virtual ~SlicedPepperoni() = default;

    virtual std::string toShow() const override;
};