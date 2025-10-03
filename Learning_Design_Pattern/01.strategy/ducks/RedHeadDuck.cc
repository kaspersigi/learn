#include "RedHeadDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <memory>
#include <print>

RedHeadDuck::RedHeadDuck()
    : Duck(std::make_unique<FlyWithWings>(), std::make_unique<Quack>())
{
}

void RedHeadDuck::display() const
{
    std::println("I'm a real Red Headed duck!");
}
