#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Whip : public CondimentDecorator {
public:
    explicit Whip(const Beverage* beverage);
    virtual ~Whip() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

protected:
    Whip(const Whip&) = delete;
    Whip(Whip&&) = delete;
    Whip& operator=(const Whip&) = delete;
    Whip& operator=(Whip&&) = delete;

private:
    std::shared_ptr<const Beverage> _beverage {};
};