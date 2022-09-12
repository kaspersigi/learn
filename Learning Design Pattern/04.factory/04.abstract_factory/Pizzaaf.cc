#include "Pizzaaf.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<PizzaStore> nyStore(new NYPizzaStore());
    std::shared_ptr<PizzaStore> chicagoStore(new ChicagoPizzaStore());

    std::shared_ptr<Pizza> pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->toShow() << std::endl;

    pizza = chicagoStore->orderPizza("cheese");
    std::cout << "Joel ordered a " << pizza->toShow() << std::endl;

    pizza = nyStore->orderPizza("clam");
    std::cout << "Ethan ordered a " << pizza->toShow() << std::endl;

    pizza = chicagoStore->orderPizza("clam");
    std::cout << "Joel ordered a " << pizza->toShow() << std::endl;

    pizza = nyStore->orderPizza("pepperoni");
    std::cout << "Ethan ordered a " << pizza->toShow() << std::endl;

    pizza = chicagoStore->orderPizza("pepperoni");
    std::cout << "Joel ordered a " << pizza->toShow() << std::endl;

    pizza = nyStore->orderPizza("veggie");
    std::cout << "Ethan ordered a " + pizza->toShow() << std::endl;

    pizza = chicagoStore->orderPizza("veggie");
    std::cout << "Joel ordered a " << pizza->toShow() << std::endl;

    return 0;
}