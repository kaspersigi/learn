#include "Chocolate.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto boiler1 = ChocolateBoiler::getInstance();
    boiler1->fill();
    boiler1->boil();
    boiler1->drain();

    auto boiler2 = ChocolateBoiler::getInstance();
    auto boiler3 = boiler2;

    if (boiler1 == boiler2)
        std::cout << "Got same boiler" << std::endl;
    else
        std::cout << "Oh oh! got a different boiler" << std::endl;

    return 0;
}