#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Soy : public CondimentDecorator {
public:
    explicit Soy(const Beverage* beverage);
    virtual ~Soy() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

protected:
    Soy(const Soy&) = delete;
    Soy(Soy&&) = delete;
    Soy& operator=(const Soy&) = delete;
    Soy& operator=(Soy&&) = delete;

private:
    std::shared_ptr<const Beverage> _beverage;
};