#include "RedHeadDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

RedHeadDuck::RedHeadDuck()
    : Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>())
{
}

void RedHeadDuck::display() const
{
    std::cout << "I'm a real Red Headed duck!" << std::endl;
}
