#include "SimplePizzaFactory.h"

std::unique_ptr<Pizza> SimplePizzaFactory::CreatePizza(const std::string& type)
{
    if (type == "cheese") {
        return std::make_unique<CheesePizza>();
    } else if (type == "pepperoni") {
        return std::make_unique<PepperoniPizza>();
    } else if (type == "clam") {
        return std::make_unique<ClamPizza>();
    } else if (type == "veggie") {
        return std::make_unique<VeggiePizza>();
    }
    return nullptr;
}