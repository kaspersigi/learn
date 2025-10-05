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

    auto darkroast = std::make_unique<DarkRoast>();
    auto darkroastWithMocha = std::make_unique<Mocha>(std::move(darkroast));
    auto darkroastWithMocha2 = std::make_unique<Mocha>(std::move(darkroastWithMocha));
    auto darkroastWithWhip = std::make_unique<Whip>(std::move(darkroastWithMocha2));
    std::cout << darkroastWithWhip->getDescription()
              << " $"
              << darkroastWithWhip->cost()
              << std::endl;

    auto houseblend = std::make_unique<HouseBlend>();
    auto houseblendWithSoy = std::make_unique<Soy>(std::move(houseblend));
    auto houseblendWithMocha = std::make_unique<Mocha>(std::move(houseblendWithSoy));
    auto houseblendWithWhip = std::make_unique<Whip>(std::move(houseblendWithMocha));
    std::cout << houseblendWithWhip->getDescription()
              << " $"
              << houseblendWithWhip->cost()
              << std::endl;

    return 0;
}