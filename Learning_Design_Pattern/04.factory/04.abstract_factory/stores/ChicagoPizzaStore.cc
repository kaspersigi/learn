#include "ChicagoPizzaStore.h"
#include "../factories/ChicagoPizzaIngredientFactory.h"
#include "../pizzas/pizzas.h"

std::shared_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string type) const
{
    PizzaIngredientFactory* ingredientFactory = new ChicagoPizzaIngredientFactory();
    std::shared_ptr<Pizza> pizza;
    if (0 == type.compare("cheese")) {
        pizza = std::shared_ptr<Pizza>(new CheesePizza(ingredientFactory));
        pizza->setName("Chicago Style Cheese Pizza");
    } else if (0 == type.compare("veggie")) {
        pizza = std::shared_ptr<Pizza>(new VeggiePizza(ingredientFactory));
        pizza->setName("Chicago Style Veggie Pizza");
    } else if (0 == type.compare("clam")) {
        pizza = std::shared_ptr<Pizza>(new ClamPizza(ingredientFactory));
        pizza->setName("Chicago Style Clam Pizza");
    } else if (0 == type.compare("pepperoni")) {
        pizza = std::shared_ptr<Pizza>(new PepperoniPizza(ingredientFactory));
        pizza->setName("Chicago Style Pepperoni Pizza");
    }
    return pizza;
}