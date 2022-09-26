#pragma once

#include "../factory/SimplePizzaFactory.h"
#include <memory>

class PizzaStore {
public:
    explicit PizzaStore(SimplePizzaFactory* factory);
    ~PizzaStore() = default;

    std::shared_ptr<Pizza> orderPizza(std::string type);

protected:
    PizzaStore(const PizzaStore&) = delete;
    PizzaStore(PizzaStore&&) = delete;
    PizzaStore& operator=(const PizzaStore&) = delete;
    PizzaStore& operator=(PizzaStore&&) = delete;

private:
    std::shared_ptr<SimplePizzaFactory> _factory;
};