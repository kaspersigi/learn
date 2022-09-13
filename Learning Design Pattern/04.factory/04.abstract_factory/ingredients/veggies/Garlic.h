#pragma once

#include "../../interface/Veggies.h"

class Garlic : public Veggies {
public:
    Garlic() = default;
    virtual ~Garlic() = default;
    virtual std::string toShow() const override;

protected:
    Garlic(const Garlic&) = delete;
    Garlic(Garlic&&) = delete;
    Garlic& operator=(const Garlic&) = delete;
    Garlic& operator=(Garlic&&) = delete;
};