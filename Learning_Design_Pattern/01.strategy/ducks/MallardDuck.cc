#include "MallardDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <memory>
#include <print>

MallardDuck::MallardDuck()
    : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Quack>())
{
}

void MallardDuck::display() const
{
    std::println("I'm a real Mallard duck!");
}
