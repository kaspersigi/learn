#include "ModelDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <iostream>

ModelDuck::ModelDuck()
    : Duck(std::make_shared<FlyNoWay>(), std::make_shared<FakeQuack>())
{
}

void ModelDuck::display() const
{
    std::cout << "I'm a model duck" << std::endl;
}
