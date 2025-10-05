#include "Pizza.h"
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto factory = std::make_unique<SimplePizzaFactory>();
    PizzaStore store(factory.get());

    {
        auto pizza = store.orderPizza("cheese");
        std::cout << "We ordered a " << pizza->getName() << std::endl;
        std::cout << pizza->toShow() << std::endl;
    }

    {
        auto pizza = store.orderPizza("veggie");
        std::cout << "We ordered a " << pizza->getName() << std::endl;
        std::cout << pizza->toShow() << std::endl;
    }

    return 0;
}