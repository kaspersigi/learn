#include "Chocolate.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    ChocolateBoiler& boiler1 = ChocolateBoiler::getInstance();
    boiler1.fill();
    boiler1.boil();
    boiler1.drain();

    ChocolateBoiler& boiler2 = ChocolateBoiler::getInstance();

    if (&boiler1 == &boiler2)
        std::cout << "Got same boiler" << std::endl;
    else
        std::cout << "Oh oh! got a different boiler" << std::endl;

    return 0;
}