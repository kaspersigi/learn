#pragma once

#include "../pizzas/pizzas.h"
#include <memory>

class SimplePizzaFactory
{
public:
    SimplePizzaFactory() = default;
    ~SimplePizzaFactory() = default;

    static std::shared_ptr<Pizza> CreatePizza(std::string type);

protected:
    SimplePizzaFactory(const SimplePizzaFactory&) = delete;
    SimplePizzaFactory(SimplePizzaFactory&&) = delete;
    SimplePizzaFactory& operator = (const SimplePizzaFactory&) = delete;
    SimplePizzaFactory& operator = (SimplePizzaFactory&&) = delete;
};