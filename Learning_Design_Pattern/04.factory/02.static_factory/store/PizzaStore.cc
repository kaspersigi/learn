#include "PizzaStore.h"
#include "../factory/SimplePizzaFactory.h"

std::unique_ptr<Pizza> PizzaStore::orderPizza(const std::string& type)
{
    auto pizza = SimplePizzaFactory::CreatePizza(type);

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}