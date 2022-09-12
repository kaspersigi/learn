#include "NYPizzaStore.h"
#include "../factories/NYPizzaIngredientFactory.h"
#include "../pizzas/pizzas.h"

std::shared_ptr<Pizza> NYPizzaStore::createPizza(std::string type) const
{
    PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory();
    std::shared_ptr<Pizza> pizza;
    if (0 == type.compare("cheese")) {
        pizza = std::shared_ptr<Pizza>(new CheesePizza(ingredientFactory));
        pizza->setName("New York Style Cheese Pizza");
    } else if (0 == type.compare("veggie")) {
        pizza = std::shared_ptr<Pizza>(new VeggiePizza(ingredientFactory));
        pizza->setName("New York Style Veggie Pizza");
    } else if (0 == type.compare("clam")) {
        pizza = std::shared_ptr<Pizza>(new ClamPizza(ingredientFactory));
        pizza->setName("New York Style Clam Pizza");
    } else if (0 == type.compare("pepperoni")) {
        pizza = std::shared_ptr<Pizza>(new PepperoniPizza(ingredientFactory));
        pizza->setName("New York Style Pepperoni Pizza");
    }
    return pizza;
}