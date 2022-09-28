#pragma once

#include "../interface/PizzaStore.h"

class ChicagoPizzaStore : public PizzaStore {
public:
    ChicagoPizzaStore() = default;
    virtual ~ChicagoPizzaStore() = default;

    virtual std::shared_ptr<Pizza> createPizza(std::string type) const override;

protected:
    ChicagoPizzaStore(const ChicagoPizzaStore&) = delete;
    ChicagoPizzaStore(ChicagoPizzaStore&&) = delete;
    ChicagoPizzaStore& operator=(const ChicagoPizzaStore&) = delete;
    ChicagoPizzaStore& operator=(ChicagoPizzaStore&&) = delete;
};