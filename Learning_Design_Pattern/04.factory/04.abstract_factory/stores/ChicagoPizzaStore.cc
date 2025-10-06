#include "ChicagoPizzaStore.h"
#include "../factories/ChicagoPizzaIngredientFactory.h"
#include "../pizzas/pizzas.h"

std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string type) const
{
    std::unique_ptr<Pizza> pizza;
    auto ingredientFactory = std::make_unique<ChicagoPizzaIngredientFactory>();
    if (type == "cheese") {
        pizza = std::make_unique<CheesePizza>(std::move(ingredientFactory));
        pizza->setName("Chicago Style Cheese Pizza");
    } else if (type == "veggie") {
        pizza = std::make_unique<VeggiePizza>(std::move(ingredientFactory));
        pizza->setName("Chicago Style Veggie Pizza");
    } else if (type == "clam") {
        pizza = std::make_unique<ClamPizza>(std::move(ingredientFactory));
        pizza->setName("Chicago Style Clam Pizza");
    } else if (type == "pepperoni") {
        pizza = std::make_unique<PepperoniPizza>(std::move(ingredientFactory));
        pizza->setName("Chicago Style Pepperoni Pizza");
    }
    return pizza;
}