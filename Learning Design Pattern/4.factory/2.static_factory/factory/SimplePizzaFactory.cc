#include "SimplePizzaFactory.h"

std::shared_ptr<Pizza> SimplePizzaFactory::CreatePizza(std::string type)
{
    Pizza* pizza = nullptr;
    if (type.compare("cheese") == 0) {
        pizza = new CheesePizza();
    } else if (type.compare("pepperoni") == 0) {
        pizza = new PepperoniPizza();
    } else if (type.compare("clam") == 0) {
        pizza = new ClamPizza();
    } else if (type.compare("veggie") == 0) {
        pizza = new VeggiePizza();
    }
    return std::shared_ptr<Pizza>(pizza);
}