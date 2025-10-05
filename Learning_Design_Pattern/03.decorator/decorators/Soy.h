#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Soy : public CondimentDecorator
{
public:
    explicit Soy(std::unique_ptr<Beverage> beverage);
    virtual ~Soy() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage {};
};