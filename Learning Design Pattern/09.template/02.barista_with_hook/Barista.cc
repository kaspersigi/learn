#include "Barista.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto coffee = std::make_shared<CoffeeWithHook>();
    auto tea = std::make_shared<TeaWithHook>();
    std::cout << std::endl
              << "Making tea..." << std::endl;
    tea->prepareRecipe();

    std::cout << std::endl
              << "Making coffee..." << std::endl;
    coffee->prepareRecipe();

    return 0;
}