#include "WildTurkey.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

WildTurkey::WildTurkey()
    : Turkey(new FlyWithWings(), new Gobble())
{
}

void WildTurkey::display() const
{
    std::cout << "I'm a wild turkey!" << std::endl;
}