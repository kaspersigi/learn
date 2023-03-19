#include "CaffeineBeverage.h"
#include <iostream>

void CaffeineBeverage::prepareRecipe()
{
    boilWater();
    brew();
    pourInCup();
    addCondiments();
}

void CaffeineBeverage::boilWater() const { std::cout << "Boiling water" << std::endl; }

void CaffeineBeverage::pourInCup() const { std::cout << "Pouring into cup" << std::endl; }