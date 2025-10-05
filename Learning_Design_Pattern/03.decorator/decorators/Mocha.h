#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Mocha : public CondimentDecorator
{
public:
    explicit Mocha(std::unique_ptr<Beverage> beverage);
    virtual ~Mocha() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage {};
};