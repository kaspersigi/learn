#include "NYPizzaIngredientFactory.h"
#include "../cheese/ReggianoCheese.h"
#include "../clams/FreshClams.h"
#include "../dough/ThinCrustDough.h"
#include "../pepperoni/SlicedPepperoni.h"
#include "../sauce/MarinaraSauce.h"
#include "../veggies/Garlic.h"
#include "../veggies/Mushroom.h"
#include "../veggies/Onion.h"
#include "../veggies/RedPepper.h"

Cheese* NYPizzaIngredientFactory::createCheese() const { return new ReggianoCheese(); }

Clams* NYPizzaIngredientFactory::createClams() const { return new FreshClams(); }

Dough* NYPizzaIngredientFactory::createDough() const { return new ThinCrustDough(); }

Pepperoni* NYPizzaIngredientFactory::createPepperoni() const { return new SlicedPepperoni(); }

Sauce* NYPizzaIngredientFactory::createSauce() const { return new MarinaraSauce(); }

std::vector<Veggies*> NYPizzaIngredientFactory::createVeggies() const
{
    std::vector<Veggies*> veggies;
    veggies.push_back(new Garlic());
    veggies.push_back(new Onion());
    veggies.push_back(new Mushroom());
    veggies.push_back(new RedPepper());
    return veggies;
}