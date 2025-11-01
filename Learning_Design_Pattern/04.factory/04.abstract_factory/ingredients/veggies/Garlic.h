#pragma once

#include "../../interface/Veggies.h"

class Garlic : public Veggies {
public:
    Garlic() = default;
    virtual ~Garlic() = default;

    virtual std::string toShow() const override;
};