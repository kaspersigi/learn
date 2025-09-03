#pragma once

#include "../interface/PizzaIngredientFactory.h"

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    NYPizzaIngredientFactory() = default;
    virtual ~NYPizzaIngredientFactory() = default;

    virtual Cheese* createCheese() const override;
    virtual Clams* createClams() const override;
    virtual Dough* createDough() const override;
    virtual Pepperoni* createPepperoni() const override;
    virtual Sauce* createSauce() const override;
    virtual std::vector<Veggies*> createVeggies() const override;

protected:
    NYPizzaIngredientFactory(const NYPizzaIngredientFactory&) = delete;
    NYPizzaIngredientFactory(NYPizzaIngredientFactory&&) = delete;
    NYPizzaIngredientFactory& operator = (const NYPizzaIngredientFactory&) = delete;
    NYPizzaIngredientFactory& operator = (NYPizzaIngredientFactory&&) = delete;
};