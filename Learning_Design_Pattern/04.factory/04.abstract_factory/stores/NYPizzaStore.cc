#include "NYPizzaStore.h"
#include "../factories/NYPizzaIngredientFactory.h"
#include "../pizzas/pizzas.h"

std::shared_ptr<Pizza> NYPizzaStore::createPizza(std::string type) const
{
    std::shared_ptr<Pizza> pizza;
    if (type == "cheese") {
        pizza = std::make_shared<CheesePizza>(
            std::make_unique<NYPizzaIngredientFactory>());
        pizza->setName("Chicago Style Cheese Pizza");
    } else if (type == "veggie") {
        pizza = std::make_shared<VeggiePizza>(
            std::make_unique<NYPizzaIngredientFactory>());
        pizza->setName("Chicago Style Veggie Pizza");
    } else if (type == "clam") {
        pizza = std::make_shared<ClamPizza>(
            std::make_unique<NYPizzaIngredientFactory>());
        pizza->setName("Chicago Style Clam Pizza");
    } else if (type == "pepperoni") {
        pizza = std::make_shared<PepperoniPizza>(
            std::make_unique<NYPizzaIngredientFactory>());
        pizza->setName("Chicago Style Pepperoni Pizza");
    }
    return pizza;
}