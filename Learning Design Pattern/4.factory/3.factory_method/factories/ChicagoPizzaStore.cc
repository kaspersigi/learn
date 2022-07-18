#include "ChicagoPizzaStore.h"
#include "../pizzas/ChicagoStylePizzas.h"

std::shared_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string type) const
{
    if (type.compare("cheese") == 0) {
        return std::shared_ptr<Pizza>(new ChicagoStyleCheesePizza());
    } else if (type.compare("veggie") == 0) {
        return std::shared_ptr<Pizza>(new ChicagoStyleVeggiePizza());
    } else if (type.compare("clam") == 0) {
        return std::shared_ptr<Pizza>(new ChicagoStyleClamPizza());
    } else if (type.compare("pepperoni") == 0) {
        return std::shared_ptr<Pizza>(new ChicagoStylePepperoniPizza());
    } else
        return std::shared_ptr<Pizza>(nullptr);
}