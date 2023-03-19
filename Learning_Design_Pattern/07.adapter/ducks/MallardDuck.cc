#include "MallardDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

MallardDuck::MallardDuck()
    : Duck(new FlyWithWings(), new Quack())
{
}

void MallardDuck::display() const
{
    std::cout << "I'm a real Mallard duck!" << std::endl;
}
