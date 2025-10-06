#include "TurkeyAdapter.h"
#include "../flyBehaviors/flyBehaviors.h"
#include "../quackBehaviors/quackBehaviors.h"

TurkeyAdapter::TurkeyAdapter(std::shared_ptr<const Turkey> turkey)
    : Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>())
    , _turkey(turkey)
{
}

void TurkeyAdapter::performFly() const { _turkey->performFly(); }

void TurkeyAdapter::performQuack() const { _turkey->performQuack(); }

void TurkeyAdapter::swim() const { _turkey->swim(); }

void TurkeyAdapter::display() const { _turkey->display(); }