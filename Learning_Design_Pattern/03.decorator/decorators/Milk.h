#pragma once

#include "../interface/CondimentDecorator.h"
#include <memory>

class Milk : public CondimentDecorator
{
public:
    explicit Milk(const Beverage* beverage);
    virtual ~Milk() = default;

    virtual std::string getDescription() const override;
    virtual double cost() const override;

protected:
    Milk(const Milk&) = delete;
    Milk(Milk&&) = delete;
    Milk& operator = (const Milk&) = delete;
    Milk& operator = (Milk&&) = delete;

private:
    std::shared_ptr<const Beverage> _beverage {};
};