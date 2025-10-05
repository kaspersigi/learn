#pragma once

#include "../interface/NonCopyable.h"
#include "../pizzas/pizzas.h"
#include <memory>

class SimplePizzaFactory : public NonCopyable
{
public:
    SimplePizzaFactory() = default;
    ~SimplePizzaFactory() = default;

    std::unique_ptr<Pizza> createPizza(const std::string& type) const;
};