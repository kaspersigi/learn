#pragma once

#include "../interface/NonCopyable.h"
#include "../interface/Pizza.h"
#include <memory>

class PizzaStore : public NonCopyable
{
public:
    explicit PizzaStore() = default;
    ~PizzaStore() = default;

    std::unique_ptr<Pizza> orderPizza(const std::string& type);
};