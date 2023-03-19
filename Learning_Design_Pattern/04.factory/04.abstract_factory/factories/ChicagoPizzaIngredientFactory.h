#pragma once

#include "../interface/PizzaIngredientFactory.h"

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    ChicagoPizzaIngredientFactory() = default;
    virtual ~ChicagoPizzaIngredientFactory() = default;

    virtual Cheese* createCheese() const override;
    virtual Clams* createClams() const override;
    virtual Dough* createDough() const override;
    virtual Pepperoni* createPepperoni() const override;
    virtual Sauce* createSauce() const override;
    virtual std::vector<Veggies*> createVeggies() const override;

protected:
    ChicagoPizzaIngredientFactory(const ChicagoPizzaIngredientFactory&) = delete;
    ChicagoPizzaIngredientFactory(ChicagoPizzaIngredientFactory&&) = delete;
    ChicagoPizzaIngredientFactory& operator=(const ChicagoPizzaIngredientFactory&) = delete;
    ChicagoPizzaIngredientFactory& operator=(ChicagoPizzaIngredientFactory&&) = delete;
};