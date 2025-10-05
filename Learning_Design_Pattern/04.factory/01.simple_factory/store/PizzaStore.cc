#include "PizzaStore.h"

PizzaStore::PizzaStore(SimplePizzaFactory* factory)
    : _factory(factory)
{
}

std::unique_ptr<Pizza> PizzaStore::orderPizza(const std::string& type)
{
    auto pizza = _factory->createPizza(type);

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}