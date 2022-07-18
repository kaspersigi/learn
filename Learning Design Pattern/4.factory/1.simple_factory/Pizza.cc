#include "Pizza.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    PizzaStore store(new SimplePizzaFactory());

    std::shared_ptr<Pizza> pizza;

    pizza = store.orderPizza("cheese");
    std::cout << "We ordered a " << pizza->getName() << std::endl;

    std::cout << "--------------------" << std::endl;

    pizza = store.orderPizza("veggie");
    std::cout << "We ordered a " << pizza->getName() << std::endl;

    return 0;
}