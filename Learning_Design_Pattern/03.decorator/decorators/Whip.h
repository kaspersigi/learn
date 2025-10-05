#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Whip : public CondimentDecorator
{
public:
    explicit Whip(std::unique_ptr<Beverage> beverage);
    virtual ~Whip() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage {};
};