#pragma once

#include <memory>

class Pizza;

class PizzaStore {
public:
    PizzaStore() = default;

    virtual std::shared_ptr<Pizza> createPizza(std::string type) const = 0;
    virtual std::shared_ptr<Pizza> orderPizza(std::string type) const;

protected:
    virtual ~PizzaStore() = default;
    PizzaStore(const PizzaStore&) = delete;
    PizzaStore(PizzaStore&&) = delete;
    PizzaStore& operator=(const PizzaStore&) = delete;
    PizzaStore& operator=(PizzaStore&&) = delete;
};