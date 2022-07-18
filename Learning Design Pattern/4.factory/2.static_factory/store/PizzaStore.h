#pragma once

#include "../interface/Pizza.h"
#include <memory>

class PizzaStore {
public:
    explicit PizzaStore() = default;
    ~PizzaStore() = default;

protected:
    PizzaStore(const PizzaStore&) = delete;
    PizzaStore(PizzaStore&&) = delete;
    PizzaStore& operator=(const PizzaStore&) = delete;
    PizzaStore& operator=(PizzaStore&&) = delete;

public:
    std::shared_ptr<Pizza> orderPizza(std::string type);
};