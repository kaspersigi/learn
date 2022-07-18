#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Mocha : public CondimentDecorator {
public:
    explicit Mocha(const Beverage* beverage);
    virtual ~Mocha() = default;

protected:
    Mocha(const Mocha&) = delete;
    Mocha(Mocha&&) = delete;
    Mocha& operator=(const Mocha&) = delete;
    Mocha& operator=(Mocha&&) = delete;

public:
    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::shared_ptr<const Beverage> _beverage;
};