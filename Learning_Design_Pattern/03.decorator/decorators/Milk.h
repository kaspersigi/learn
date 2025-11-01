#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Beverage;

class Milk : public CondimentDecorator {
public:
    explicit Milk(std::unique_ptr<Beverage> beverage);
    ~Milk() override;

    std::string getDescription() const override;
    double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage;
};