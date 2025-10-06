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
#include <memory>

std::unique_ptr<Dough> NYPizzaIngredientFactory::createDough() const
{
    return std::make_unique<ThinCrustDough>();
}

std::unique_ptr<Sauce> NYPizzaIngredientFactory::createSauce() const
{
    return std::make_unique<MarinaraSauce>();
}

std::unique_ptr<Cheese> NYPizzaIngredientFactory::createCheese() const
{
    return std::make_unique<ReggianoCheese>();
}

std::vector<std::unique_ptr<Veggies>> NYPizzaIngredientFactory::createVeggies() const
{
    std::vector<std::unique_ptr<Veggies>> veggies;
    veggies.push_back(std::make_unique<Garlic>());
    veggies.push_back(std::make_unique<Onion>());
    veggies.push_back(std::make_unique<Mushroom>());
    veggies.push_back(std::make_unique<RedPepper>());
    return veggies;
}

std::unique_ptr<Pepperoni> NYPizzaIngredientFactory::createPepperoni() const
{
    return std::make_unique<SlicedPepperoni>();
}

std::unique_ptr<Clams> NYPizzaIngredientFactory::createClams() const
{
    return std::make_unique<FreshClams>();
}