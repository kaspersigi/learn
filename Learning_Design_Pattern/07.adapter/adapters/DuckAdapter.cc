#include "DuckAdapter.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"

DuckAdapter::DuckAdapter(const Duck* duck)
    : Turkey(new FlyWithWings(), new Gobble())
    , _duck(duck)
{
}

void DuckAdapter::performFly() const { _duck->performFly(); }

void DuckAdapter::performQuack() const { _duck->performQuack(); }

void DuckAdapter::swim() const { _duck->swim(); }

void DuckAdapter::display() const { _duck->display(); }