#include "Barista.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<CaffeineBeverageWithHook> coffee = std::make_shared<CoffeeWithHook>();
    std::shared_ptr<CaffeineBeverageWithHook> tea = std::make_shared<TeaWithHook>();
    std::cout << std::endl
              << "Making tea..." << std::endl;
    tea->prepareRecipe();

    std::cout << std::endl
              << "Making coffee..." << std::endl;
    coffee->prepareRecipe();

    return 0;
}