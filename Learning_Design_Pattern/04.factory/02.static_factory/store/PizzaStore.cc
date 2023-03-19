#include "PizzaStore.h"
#include "../factory/SimplePizzaFactory.h"
#include <cassert>

std::shared_ptr<Pizza> PizzaStore::orderPizza(std::string type)
{
    auto pizza = SimplePizzaFactory::CreatePizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}