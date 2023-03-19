#include "DecoyDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

DecoyDuck::DecoyDuck()
    : Duck(new FlyNoWay(), new MuteQuack())
{
}

void DecoyDuck::display() const
{
    std::cout << "I'm a duck Decoy!" << std::endl;
}
