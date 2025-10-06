#include "NYPizzaStore.h"
#include "../pizzas/NYStylePizzas.h"

std::unique_ptr<Pizza> NYPizzaStore::createPizza(std::string type) const
{
    if (type.compare("cheese") == 0) {
        return std::make_unique<NYStyleCheesePizza>();
    } else if (type.compare("veggie") == 0) {
        return std::make_unique<NYStyleVeggiePizza>();
    } else if (type.compare("clam") == 0) {
        return std::make_unique<NYStyleClamPizza>();
    } else if (type.compare("pepperoni") == 0) {
        return std::make_unique<NYStylePepperoniPizza>();
    } else
        return std::unique_ptr<Pizza>(nullptr);
}