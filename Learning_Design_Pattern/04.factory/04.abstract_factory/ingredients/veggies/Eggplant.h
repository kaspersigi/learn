#pragma once

#include "../../interface/Veggies.h"

class Eggplant : public Veggies
{
public:
    Eggplant() = default;
    virtual ~Eggplant() = default;

    virtual std::string toShow() const override;
};