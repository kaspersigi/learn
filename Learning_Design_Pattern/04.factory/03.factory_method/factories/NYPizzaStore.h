#pragma once

#include "../interface/PizzaStore.h"

class NYPizzaStore : public PizzaStore
{
public:
    NYPizzaStore() = default;
    virtual ~NYPizzaStore() = default;

    virtual std::unique_ptr<Pizza> createPizza(std::string type) const override;
};