#include "NYPizzaIngredientFactory.h"
#include "../ingredients/cheese/ReggianoCheese.h"
#include "../ingredients/clams/FreshClams.h"
#include "../ingredients/dough/ThinCrustDough.h"
#include "../ingredients/pepperoni/SlicedPepperoni.h"
#include "../ingredients/sauce/MarinaraSauce.h"
#include "../ingredients/veggies/Garlic.h"
#include "../ingredients/veggies/Mushroom.h"
#include "../ingredients/veggies/Onion.h"
#include "../ingredients/veggies/RedPepper.h"

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