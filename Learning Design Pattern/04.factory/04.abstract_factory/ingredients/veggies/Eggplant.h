#pragma once

#include "../../interface/Veggies.h"

class Eggplant : public Veggies {
public:
    Eggplant() = default;
    virtual ~Eggplant() = default;

    virtual std::string toShow() const override;

protected:
    Eggplant(const Eggplant&) = delete;
    Eggplant(Eggplant&&) = delete;
    Eggplant& operator=(const Eggplant&) = delete;
    Eggplant& operator=(Eggplant&&) = delete;
};