#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Beverage;

class Whip : public CondimentDecorator {
public:
    explicit Whip(std::unique_ptr<Beverage> beverage);
    ~Whip() override;

    std::string getDescription() const override;
    double cost() const override;

private:
    std::unique_ptr<Beverage> _beverage;
};