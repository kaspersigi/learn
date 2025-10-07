#include "Duck.h"
#include "../interface/FlyBehavior.h"
#include "../interface/QuackBehavior.h"
#include <iostream>

Duck::Duck(std::shared_ptr<FlyBehavior> flyBehavior, std::shared_ptr<QuackBehavior> quackBehavior)
    : _flyBehavior(flyBehavior)
    , _quackBehavior(quackBehavior)
{
}

Duck::~Duck() = default;

void Duck::setFlyBehavior(std::shared_ptr<FlyBehavior> flyBehavior)
{
    _flyBehavior = flyBehavior;
}

void Duck::setQuackBehavior(std::shared_ptr<QuackBehavior> quackBehavior)
{
    _quackBehavior = quackBehavior;
}

void Duck::performFly() const
{
    _flyBehavior->fly();
}

void Duck::performQuack() const
{
    _quackBehavior->quack();
}

void Duck::swim() const
{
    std::cout << "All ducks float, even decoys!" << std::endl;
}