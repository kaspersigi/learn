#include "Starbuzz.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<Beverage> espresso = std::make_shared<Espresso>();
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(3);
    std::cout << espresso->getDescription()
              << " $"
              << espresso->cost()
              << std::endl;

    Beverage* darkroast = new DarkRoast();
    darkroast = new Mocha(darkroast);
    darkroast = new Mocha(darkroast);
    darkroast = new Whip(darkroast);
    std::cout << darkroast->getDescription()
              << " $"
              << darkroast->cost()
              << std::endl;

    Beverage* houseblend = new HouseBlend();
    houseblend = new Soy(houseblend);
    houseblend = new Mocha(houseblend);
    houseblend = new Whip(houseblend);
    std::cout << houseblend->getDescription()
              << " $"
              << houseblend->cost()
              << std::endl;

    delete darkroast;
    delete houseblend;

    return 0;
}