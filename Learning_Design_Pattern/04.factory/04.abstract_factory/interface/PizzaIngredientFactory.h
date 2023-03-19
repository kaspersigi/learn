#pragma once

#include <vector>

class Cheese;
class Clams;
class Dough;
class Pepperoni;
class Sauce;
class Veggies;

class PizzaIngredientFactory {
public:
    virtual ~PizzaIngredientFactory() = default;

    virtual Cheese* createCheese() const = 0;
    virtual Clams* createClams() const = 0;
    virtual Dough* createDough() const = 0;
    virtual Pepperoni* createPepperoni() const = 0;
    virtual Sauce* createSauce() const = 0;
    virtual std::vector<Veggies*> createVeggies() const = 0;

protected:
    PizzaIngredientFactory() = default;
    PizzaIngredientFactory(const PizzaIngredientFactory&) = delete;
    PizzaIngredientFactory(PizzaIngredientFactory&&) = delete;
    PizzaIngredientFactory& operator=(const PizzaIngredientFactory&) = delete;
    PizzaIngredientFactory& operator=(PizzaIngredientFactory&&) = delete;
};