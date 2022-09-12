#pragma once

#include "../interface/Veggies.h"

class Spinach : public Veggies {
public:
    Spinach() = default;
    virtual ~Spinach() = default;
    virtual std::string toShow() const override;

protected:
    Spinach(const Spinach&) = delete;
    Spinach(Spinach&&) = delete;
    Spinach& operator=(const Spinach&) = delete;
    Spinach& operator=(Spinach&&) = delete;
};