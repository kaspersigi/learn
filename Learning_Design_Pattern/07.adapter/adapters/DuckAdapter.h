#pragma once

#include "../interface/Turkey.h"
#include <memory>

class Duck;

class DuckAdapter : public Turkey
{
public:
    explicit DuckAdapter(std::shared_ptr<const Duck> duck);
    virtual ~DuckAdapter();

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

private:
    std::shared_ptr<const Duck> _duck;
};