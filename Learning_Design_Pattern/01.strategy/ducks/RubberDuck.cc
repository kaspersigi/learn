#include "RubberDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <memory>
#include <print>

RubberDuck::RubberDuck()
    : Duck(std::make_unique<FlyNoWay>(), std::make_unique<Squeak>())
{
}

void RubberDuck::display() const
{
    std::println("I'm a rubber duck!");
}
