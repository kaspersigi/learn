#include "Duck.h"
#include "../interface/FlyBehavior.h"
#include "../interface/QuackBehavior.h"
#include <print>

Duck::Duck(std::unique_ptr<FlyBehavior> flyBehavior, std::unique_ptr<QuackBehavior> quackBehavior)
    : _flyBehavior(std::move(flyBehavior))
    , _quackBehavior(std::move(quackBehavior))
{
}

Duck::~Duck() = default;

void Duck::setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior)
{
    _flyBehavior = std::move(flyBehavior);
}

void Duck::setQuackBehavior(std::unique_ptr<QuackBehavior> quackBehavior)
{
    _quackBehavior = std::move(quackBehavior);
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
    std::println("All ducks float, even decoys!");
}
