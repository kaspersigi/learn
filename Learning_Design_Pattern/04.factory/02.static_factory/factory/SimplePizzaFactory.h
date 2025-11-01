#pragma once

#include "../interface/NonCopyable.h"
#include "../pizzas/pizzas.h"
#include <memory>

class SimplePizzaFactory : public NonCopyable {
public:
    SimplePizzaFactory() = default;
    ~SimplePizzaFactory() = default;

    static std::unique_ptr<Pizza> CreatePizza(const std::string& type);
};