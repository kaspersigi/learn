#include "PizzaStore.h"

std::shared_ptr<Pizza> PizzaStore::orderPizza(std::string type) const
{
    auto pizza = createPizza(type);
    std::cout << "--- Making a " << pizza->getName() << " ---" << std::endl;
    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();
    return pizza;
}