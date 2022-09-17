#include "Duck.h"
#include "../interface/FlyBehavior.h"
#include "../interface/QuackBehavior.h"
#include <cassert>
#include <iostream>

Duck::Duck(FlyBehavior* flyBehavior, QuackBehavior* quackBehavior)
    : _flyBehavior(flyBehavior)
    , _quackBehavior(quackBehavior)
{
    assert(flyBehavior);
    assert(quackBehavior);
}

void Duck::setFlyBehavior(FlyBehavior* flyBehavior)
{
    assert(flyBehavior);
    _flyBehavior = std::shared_ptr<FlyBehavior>(flyBehavior);
}

void Duck::setQuackBehavior(QuackBehavior* quackBehavior)
{
    assert(quackBehavior);
    _quackBehavior = std::shared_ptr<QuackBehavior>(quackBehavior);
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
