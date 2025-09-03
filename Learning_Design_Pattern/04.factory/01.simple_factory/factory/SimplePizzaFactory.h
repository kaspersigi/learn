#pragma once

#include "../pizzas/pizzas.h"
#include <memory>

class SimplePizzaFactory
{
public:
    SimplePizzaFactory() = default;
    ~SimplePizzaFactory() = default;

    std::shared_ptr<Pizza> createPizza(std::string type) const;

protected:
    SimplePizzaFactory(const SimplePizzaFactory&) = delete;
    SimplePizzaFactory(SimplePizzaFactory&&) = delete;
    SimplePizzaFactory& operator = (const SimplePizzaFactory&) = delete;
    SimplePizzaFactory& operator = (SimplePizzaFactory&&) = delete;
};