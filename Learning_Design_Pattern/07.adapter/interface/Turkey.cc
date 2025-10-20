#include "Turkey.h"
#include "../interface/FlyBehavior.h"
#include "../interface/QuackBehavior.h"
#include <iostream>

Turkey::Turkey(std::shared_ptr<FlyBehavior> flyBehavior, std::shared_ptr<QuackBehavior> quackBehavior)
    : _flyBehavior(std::move(flyBehavior))
    , _quackBehavior(std::move(quackBehavior))
{
}

Turkey::~Turkey() = default;

void Turkey::setFlyBehavior(std::shared_ptr<FlyBehavior> flyBehavior)
{
    _flyBehavior = std::move(flyBehavior);
}

void Turkey::setQuackBehavior(std::shared_ptr<QuackBehavior> quackBehavior)
{
    _quackBehavior = std::move(quackBehavior);
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