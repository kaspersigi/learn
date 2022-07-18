#pragma once

#include "../interface/Beverage.h"

class Decaf : public Beverage {
public:
    Decaf();
    virtual ~Decaf() = default;

protected:
    Decaf(const Decaf&) = delete;
    Decaf(Decaf&&) = delete;
    Decaf& operator=(const Decaf&) = delete;
    Decaf& operator=(Decaf&&) = delete;

public:
    virtual double cost() const override;
};