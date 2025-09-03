#pragma once

#include "../interface/PizzaStore.h"

class NYPizzaStore : public PizzaStore
{
public:
    NYPizzaStore() = default;
    virtual ~NYPizzaStore() = default;

    virtual std::shared_ptr<Pizza> createPizza(std::string type) const override;

protected:
    NYPizzaStore(const NYPizzaStore&) = delete;
    NYPizzaStore(NYPizzaStore&&) = delete;
    NYPizzaStore& operator = (const NYPizzaStore&) = delete;
    NYPizzaStore& operator = (NYPizzaStore&&) = delete;
};