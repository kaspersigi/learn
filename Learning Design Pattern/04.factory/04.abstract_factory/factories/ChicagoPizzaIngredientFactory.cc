#include "ChicagoPizzaIngredientFactory.h"
#include "../cheese/MozzarellaCheese.h"
#include "../clams/FrozenClams.h"
#include "../dough/ThickCrustDough.h"
#include "../pepperoni/SlicedPepperoni.h"
#include "../sauce/PlumTomatoSauce.h"
#include "../veggies/BlackOlives.h"
#include "../veggies/Eggplant.h"
#include "../veggies/Spinach.h"

Cheese* ChicagoPizzaIngredientFactory::createCheese() const { return new MozzarellaCheese(); }

Clams* ChicagoPizzaIngredientFactory::createClams() const { return new FrozenClams(); }

Dough* ChicagoPizzaIngredientFactory::createDough() const { return new ThickCrustDough(); }

Pepperoni* ChicagoPizzaIngredientFactory::createPepperoni() const { return new SlicedPepperoni(); }

Sauce* ChicagoPizzaIngredientFactory::createSauce() const { return new PlumTomatoSauce(); }

std::vector<Veggies*> ChicagoPizzaIngredientFactory::createVeggies() const
{
    std::vector<Veggies*> value;
    value.push_back(new BlackOlives());
    value.push_back(new Spinach());
    value.push_back(new Eggplant());
    return value;
}