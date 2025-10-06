#pragma once

#include "../interface/PizzaIngredientFactory.h"
#include <memory>

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    NYPizzaIngredientFactory() = default;
    virtual ~NYPizzaIngredientFactory() = default;

    virtual std::unique_ptr<Dough> createDough() const override;
    virtual std::unique_ptr<Sauce> createSauce() const override;
    virtual std::unique_ptr<Cheese> createCheese() const override;
    virtual std::vector<std::unique_ptr<Veggies>> createVeggies() const override;
    virtual std::unique_ptr<Pepperoni> createPepperoni() const override;
    virtual std::unique_ptr<Clams> createClams() const override;
};