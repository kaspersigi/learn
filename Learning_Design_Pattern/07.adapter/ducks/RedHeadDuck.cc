#include "RedHeadDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

RedHeadDuck::RedHeadDuck()
    : Duck(new FlyWithWings(), new Quack())
{
}

void RedHeadDuck::display() const
{
    std::cout << "I'm a real Red Headed duck!" << std::endl;
}
