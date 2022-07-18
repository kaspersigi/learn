#include "NYPizzaStore.h"
#include "../pizzas/NYStylePizzas.h"

std::shared_ptr<Pizza> NYPizzaStore::createPizza(std::string type) const
{
    if (type.compare("cheese") == 0) {
        return std::shared_ptr<Pizza>(new NYStyleCheesePizza());
    } else if (type.compare("veggie") == 0) {
        return std::shared_ptr<Pizza>(new NYStyleVeggiePizza());
    } else if (type.compare("clam") == 0) {
        return std::shared_ptr<Pizza>(new NYStyleClamPizza());
    } else if (type.compare("pepperoni") == 0) {
        return std::shared_ptr<Pizza>(new NYStylePepperoniPizza());
    } else
        return std::shared_ptr<Pizza>(nullptr);
}