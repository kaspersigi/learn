#pragma once

#include "Pizza.h"
#include <string>

class PizzaStore {
public:
    virtual ~PizzaStore() = default;

    std::shared_ptr<Pizza> orderPizza(std::string type) const;
    virtual std::shared_ptr<Pizza> createPizza(std::string type) const = 0;

protected:
    PizzaStore() = default;
    PizzaStore(const PizzaStore&) = delete;
    PizzaStore(PizzaStore&&) = delete;
    PizzaStore& operator=(const PizzaStore&) = delete;
    PizzaStore& operator=(PizzaStore&&) = delete;
};