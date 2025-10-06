#include "ChicagoPizzaStore.h"
#include "../pizzas/ChicagoStylePizzas.h"

std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(std::string type) const
{
    if (type.compare("cheese") == 0) {
        return std::make_unique<ChicagoStyleCheesePizza>();
    } else if (type.compare("veggie") == 0) {
        return std::make_unique<ChicagoStyleVeggiePizza>();
    } else if (type.compare("clam") == 0) {
        return std::make_unique<ChicagoStyleClamPizza>();
    } else if (type.compare("pepperoni") == 0) {
        return std::make_unique<ChicagoStylePepperoniPizza>();
    } else
        return std::unique_ptr<Pizza>(nullptr);
}