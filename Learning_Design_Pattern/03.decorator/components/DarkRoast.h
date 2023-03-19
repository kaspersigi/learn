#pragma once

#include "../interface/Beverage.h"

class DarkRoast : public Beverage {
public:
    DarkRoast();
    virtual ~DarkRoast() = default;

    virtual double cost() const override;

protected:
    DarkRoast(const DarkRoast&) = delete;
    DarkRoast(DarkRoast&&) = delete;
    DarkRoast& operator=(const DarkRoast&) = delete;
    DarkRoast& operator=(DarkRoast&&) = delete;
};