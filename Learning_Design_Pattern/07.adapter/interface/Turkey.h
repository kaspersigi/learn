#pragma once

#include "NonCopyable.h"
#include <memory>

class FlyBehavior;
class QuackBehavior;

class Turkey : public NonCopyable {
public:
    virtual ~Turkey();

    void setFlyBehavior(std::shared_ptr<FlyBehavior> flyBehavior);
    void setQuackBehavior(std::shared_ptr<QuackBehavior> quackBehavior);
    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const = 0;

protected:
    Turkey(std::shared_ptr<FlyBehavior> flyBehavior, std::shared_ptr<QuackBehavior> quackBehavior);

private:
    std::shared_ptr<FlyBehavior> _flyBehavior;
    std::shared_ptr<QuackBehavior> _quackBehavior;
};