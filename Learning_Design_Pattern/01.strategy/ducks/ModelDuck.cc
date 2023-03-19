#include "ModelDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

ModelDuck::ModelDuck()
    : Duck(new FlyNoWay(), new FakeQuack())
{
}

void ModelDuck::display() const
{
    std::cout << "I'm a model duck" << std::endl;
}
