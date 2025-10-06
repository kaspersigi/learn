#pragma once

#include "NonCopyable.h"
#include <memory>
#include <vector>

class Cheese;
class Clams;
class Dough;
class Pepperoni;
class Sauce;
class Veggies;

class PizzaIngredientFactory : public NonCopyable
{
public:
    virtual ~PizzaIngredientFactory() = default;

    virtual std::unique_ptr<Cheese> createCheese() const = 0;
    virtual std::unique_ptr<Clams> createClams() const = 0;
    virtual std::unique_ptr<Dough> createDough() const = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() const = 0;
    virtual std::unique_ptr<Sauce> createSauce() const = 0;
    virtual std::vector<std::unique_ptr<Veggies>> createVeggies() const = 0;

protected:
    PizzaIngredientFactory() = default;
};