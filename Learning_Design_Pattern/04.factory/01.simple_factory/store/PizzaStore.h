#pragma once

#include "../factory/SimplePizzaFactory.h"
#include "../interface/NonCopyable.h"
#include <memory>

class PizzaStore : public NonCopyable
{
public:
    explicit PizzaStore(SimplePizzaFactory * factory);
    ~PizzaStore() = default;

    std::unique_ptr<Pizza> orderPizza(const std::string& type);

private:
    SimplePizzaFactory* _factory;
};