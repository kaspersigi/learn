#include "Barista.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<CaffeineBeverage> coffee = std::make_shared<Coffee>();
    std::shared_ptr<CaffeineBeverage> tea = std::make_shared<Tea>();
    std::cout << std::endl
              << "Making tea..." << std::endl;
    tea->prepareRecipe();

    std::cout << std::endl
              << "Making coffee..." << std::endl;
    coffee->prepareRecipe();

    return 0;
}