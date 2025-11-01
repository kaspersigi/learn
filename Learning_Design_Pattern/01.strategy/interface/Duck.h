#pragma once

#include "NonCopyable.h"
#include <memory>

class FlyBehavior;
class QuackBehavior;

class Duck : public NonCopyable {
public:
    virtual ~Duck();

    void setFlyBehavior(std::unique_ptr<FlyBehavior> flyBehavior);
    void setQuackBehavior(std::unique_ptr<QuackBehavior> quackBehavior);
    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const = 0;

protected:
    Duck(std::unique_ptr<FlyBehavior> flyBehavior, std::unique_ptr<QuackBehavior> quackBehavior);

private:
    std::unique_ptr<FlyBehavior> _flyBehavior {};
    std::unique_ptr<QuackBehavior> _quackBehavior {};
};