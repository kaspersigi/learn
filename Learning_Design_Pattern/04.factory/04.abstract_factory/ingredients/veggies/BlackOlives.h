#pragma once

#include "../../interface/Veggies.h"

class BlackOlives : public Veggies {
public:
    BlackOlives() = default;
    virtual ~BlackOlives() = default;

    virtual std::string toShow() const override;
};