#include "DecoyDuck.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"
#include <memory>
#include <print>

DecoyDuck::DecoyDuck()
    : Duck(std::make_unique<FlyNoWay>(), std::make_unique<MuteQuack>())
{
}

void DecoyDuck::display() const
{
    std::println("I'm a duck Decoy!");
}
