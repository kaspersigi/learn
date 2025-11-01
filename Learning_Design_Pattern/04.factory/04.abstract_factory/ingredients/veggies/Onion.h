#pragma once

#include "../../interface/Veggies.h"

class Onion : public Veggies {
public:
    Onion() = default;
    virtual ~Onion() = default;

    virtual std::string toShow() const override;
};