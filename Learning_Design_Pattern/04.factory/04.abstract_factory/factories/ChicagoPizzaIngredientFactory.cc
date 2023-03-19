#include "ChicagoPizzaIngredientFactory.h"
#include "../ingredients/cheese/MozzarellaCheese.h"
#include "../ingredients/clams/FrozenClams.h"
#include "../ingredients/dough/ThickCrustDough.h"
#include "../ingredients/pepperoni/SlicedPepperoni.h"
#include "../ingredients/sauce/PlumTomatoSauce.h"
#include "../ingredients/veggies/BlackOlives.h"
#include "../ingredients/veggies/Eggplant.h"
#include "../ingredients/veggies/Spinach.h"

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