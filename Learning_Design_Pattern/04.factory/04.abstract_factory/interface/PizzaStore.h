#pragma once

#include "NonCopyable.h"
#include "Pizza.h"
#include <memory>
#include <string>

class PizzaStore : public NonCopyable
{
public:
    virtual ~PizzaStore() = default;

    std::unique_ptr<Pizza> orderPizza(std::string type) const;
    virtual std::unique_ptr<Pizza> createPizza(std::string type) const = 0;

protected:
    PizzaStore() = default;
};