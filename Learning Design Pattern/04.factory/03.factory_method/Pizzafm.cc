#include "Pizzafm.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<PizzaStore> nyStore = std::make_shared<NYPizzaStore>();
    std::shared_ptr<PizzaStore> chicagoStore = std::make_shared<ChicagoPizzaStore>();

    std::shared_ptr<Pizza> pizza {};

    pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = chicagoStore->orderPizza("cheese");
    std::cout << "Joel ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = nyStore->orderPizza("clam");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = chicagoStore->orderPizza("clam");
    std::cout << "Joel ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = nyStore->orderPizza("pepperoni");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = chicagoStore->orderPizza("pepperoni");
    std::cout << "Joel ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = nyStore->orderPizza("veggie");
    std::cout << "Ethan ordered a " << pizza->getName() << std::endl;

    std::cout << "-----------------------------------------------" << std::endl;

    pizza = chicagoStore->orderPizza("veggie");
    std::cout << "Joel ordered a " << pizza->getName() << std::endl;

    return 0;
}