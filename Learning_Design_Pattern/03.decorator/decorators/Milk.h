#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Milk : public CondimentDecorator
{
public:
    explicit Milk(std::unique_ptr<Beverage> beverage);
    virtual ~Milk() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage {};
};