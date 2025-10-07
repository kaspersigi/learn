#include "WildTurkey.h"
#include "../flyBehaviors/FlyWithWings.h"
#include "../quackBehaviors/Gobble.h"
#include <iostream>

WildTurkey::WildTurkey()
    : Turkey(std::make_shared<FlyWithWings>(), std::make_shared<Gobble>())
{
}

void WildTurkey::display() const
{
    std::cout << "I'm a wild turkey!" << std::endl;
}