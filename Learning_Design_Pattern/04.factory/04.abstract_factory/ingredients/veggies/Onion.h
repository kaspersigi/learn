#pragma once

#include "../../interface/Veggies.h"

class Onion : public Veggies
{
public:
    Onion() = default;
    virtual ~Onion() = default;

    virtual std::string toShow() const override;

protected:
    Onion(const Onion&) = delete;
    Onion(Onion&&) = delete;
    Onion& operator = (const Onion&) = delete;
    Onion& operator = (Onion&&) = delete;
};