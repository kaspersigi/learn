#include "Turkey.h"
#include "../interface/FlyBehavior.h"
#include "../interface/QuackBehavior.h"
#include <cassert>
#include <iostream>

Turkey::Turkey(std::shared_ptr<FlyBehavior> flyBehavior, std::shared_ptr<QuackBehavior> quackBehavior)
    : _flyBehavior(flyBehavior)
    , _quackBehavior(quackBehavior)
{
    assert(flyBehavior);
    assert(quackBehavior);
}

void Turkey::setFlyBehavior(std::shared_ptr<FlyBehavior> flyBehavior)
{
    assert(flyBehavior);
    _flyBehavior = flyBehavior;
}

void Turkey::setQuackBehavior(std::shared_ptr<QuackBehavior> quackBehavior)
{
    assert(quackBehavior);
    _quackBehavior = quackBehavior;
}

void Turkey::performFly() const
{
    _flyBehavior->fly();
}

void Turkey::performQuack() const
{
    _quackBehavior->quack();
}

void Turkey::swim() const
{
    std::cout << "All Turkeys float, even decoys!" << std::endl;
}