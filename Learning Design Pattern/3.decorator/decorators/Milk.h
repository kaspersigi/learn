#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Milk : public CondimentDecorator {
public:
    explicit Milk(const Beverage* beverage);
    virtual ~Milk() = default;

protected:
    Milk(const Milk&) = delete;
    Milk(Milk&&) = delete;
    Milk& operator=(const Milk&) = delete;
    Milk& operator=(Milk&&) = delete;

public:
    virtual std::string getDescription() const override;
    virtual double cost() const override;

private:
    std::shared_ptr<const Beverage> _beverage;
};