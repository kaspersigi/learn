#include "PizzaStore.h"
#include <cassert>

PizzaStore::PizzaStore(SimplePizzaFactory* factory)
    : _factory(factory)
{
    assert(factory);
}

std::shared_ptr<Pizza> PizzaStore::orderPizza(std::string type)
{
    std::shared_ptr<Pizza> pizza = _factory->createPizza(type);
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}