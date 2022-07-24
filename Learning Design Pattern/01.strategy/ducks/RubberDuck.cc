#include "RubberDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

RubberDuck::RubberDuck()
    : Duck(new FlyNoWay(), new Squeak())
{
}

void RubberDuck::display() const
{
    std::cout << "I'm a rubber duck!" << std::endl;
}
