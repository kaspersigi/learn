#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Whip : public CondimentDecorator {
public:
    explicit Whip(const Beverage* beverage);
    virtual ~Whip() = default;

protected:
    Whip(const Whip&) = delete;
    Whip(Whip&&) = delete;
    Whip& operator=(const Whip&) = delete;
    Whip& operator=(Whip&&) = delete;

public:
    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::shared_ptr<const Beverage> _beverage;
};