#include "DecoyDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

DecoyDuck::DecoyDuck()
    : Duck(std::make_shared<FlyNoWay>(), std::make_shared<MuteQuack>())
{
}

void DecoyDuck::display() const
{
    std::cout << "I'm a duck Decoy!" << std::endl;
}
