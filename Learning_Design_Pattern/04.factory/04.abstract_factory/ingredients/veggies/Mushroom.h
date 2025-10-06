#pragma once

#include "../../interface/Veggies.h"

class Mushroom : public Veggies
{
public:
    Mushroom() = default;
    virtual ~Mushroom() = default;

    virtual std::string toShow() const override;
};