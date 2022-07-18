#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Soy : public CondimentDecorator {
public:
    explicit Soy(const Beverage* beverage);
    virtual ~Soy() = default;

protected:
    Soy(const Soy&) = delete;
    Soy(Soy&&) = delete;
    Soy& operator=(const Soy&) = delete;
    Soy& operator=(Soy&&) = delete;

public:
    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::shared_ptr<const Beverage> _beverage;
};