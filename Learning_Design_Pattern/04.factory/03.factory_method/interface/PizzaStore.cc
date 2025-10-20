#include "PizzaStore.h"
#include "Pizza.h"
#include <iostream>

std::unique_ptr<Pizza> PizzaStore::orderPizza(std::string type) const
{
    auto pizza = createPizza(std::move(type));
    std::cout << "--- Making a " << pizza->getName() << " ---" << std::endl;
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}