#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Beverage;

class Mocha : public CondimentDecorator
{
public:
    explicit Mocha(std::unique_ptr<Beverage> beverage);
    ~Mocha() override;

    std::string getDescription() const override;
    double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage;
};