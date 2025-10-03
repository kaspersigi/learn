#include "ModelDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <memory>
#include <print>

ModelDuck::ModelDuck()
    : Duck(std::make_unique<FlyNoWay>(), std::make_unique<FakeQuack>())
{
}

void ModelDuck::display() const
{
    std::println("I'm a model duck");
}
