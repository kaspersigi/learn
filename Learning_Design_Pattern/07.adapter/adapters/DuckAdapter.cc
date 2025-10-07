#include "DuckAdapter.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../interface/Duck.h"
#include "../quackBehaviors/quackBehaviors.h"

DuckAdapter::DuckAdapter(std::shared_ptr<const Duck> duck)
    : Turkey(std::make_shared<FlyWithWings>(), std::make_shared<Gobble>())
    , _duck(duck)
{
}

DuckAdapter::~DuckAdapter() = default;

void DuckAdapter::performFly() const { _duck->performFly(); }

void DuckAdapter::performQuack() const { _duck->performQuack(); }

void DuckAdapter::swim() const { _duck->swim(); }

void DuckAdapter::display() const { _duck->display(); }