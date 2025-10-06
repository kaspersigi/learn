#pragma once

#include "NonCopyable.h"
#include <memory>

class Pizza;

class PizzaStore : NonCopyable
{
public:
    virtual ~PizzaStore() = default;

    virtual std::unique_ptr<Pizza> createPizza(std::string type) const = 0;
    virtual std::unique_ptr<Pizza> orderPizza(std::string type) const;

protected:
    PizzaStore() = default;
};