#include "TurkeyAdapter.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"

TurkeyAdapter::TurkeyAdapter(const Turkey* turkey)
    : Duck(new FlyWithWings(), new Quack())
    , _turkey(turkey)
{
}

void TurkeyAdapter::performFly() const { _turkey->performFly(); }

void TurkeyAdapter::performQuack() const { _turkey->performQuack(); }

void TurkeyAdapter::swim() const { _turkey->swim(); }

void TurkeyAdapter::display() const { _turkey->display(); }