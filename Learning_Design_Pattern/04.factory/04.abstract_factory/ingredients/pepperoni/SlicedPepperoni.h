#pragma once

#include "../../interface/Pepperoni.h"
#include <string>

class SlicedPepperoni : public Pepperoni
{
public:
    SlicedPepperoni() = default;
    virtual ~SlicedPepperoni() = default;

    virtual std::string toShow() const override;

protected:
    SlicedPepperoni(const SlicedPepperoni&) = delete;
    SlicedPepperoni(SlicedPepperoni&&) = delete;
    SlicedPepperoni& operator = (const SlicedPepperoni&) = delete;
    SlicedPepperoni& operator = (SlicedPepperoni&&) = delete;
};