#pragma once

#include "../interface/PizzaStore.h"

class ChicagoPizzaStore : public PizzaStore {
public:
    ChicagoPizzaStore() = default;
    virtual ~ChicagoPizzaStore() = default;

    virtual std::unique_ptr<Pizza> createPizza(std::string type) const override;
};