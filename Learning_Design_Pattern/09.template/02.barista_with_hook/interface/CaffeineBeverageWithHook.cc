#include "CaffeineBeverageWithHook.h"
#include <iostream>

void CaffeineBeverageWithHook::prepareRecipe()
{
    boilWater();
    brew();
    pourInCup();
    if (customerWantsCondiments()) {
        addCondiments();
    }
}

void CaffeineBeverageWithHook::boilWater() const { std::cout << "Boiling water" << std::endl; }

void CaffeineBeverageWithHook::pourInCup() const { std::cout << "Pouring into cup" << std::endl; }

bool CaffeineBeverageWithHook::customerWantsCondiments() const { return true; }