#include "RubberDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

RubberDuck::RubberDuck()
    : Duck(std::make_shared<FlyNoWay>(), std::make_shared<Squeak>())
{
}

void RubberDuck::display() const
{
    std::cout << "I'm a rubber duck!" << std::endl;
}
