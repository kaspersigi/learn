#include "WildTurkey.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

WildTurkey::WildTurkey()
    : Turkey(std::make_shared<FlyWithWings>(), std::make_shared<Gobble>())
{
}

void WildTurkey::display() const
{
    std::cout << "I'm a wild turkey!" << std::endl;
}