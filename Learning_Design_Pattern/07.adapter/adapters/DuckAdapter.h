#pragma once

#include "../interface/Duck.h"
#include "../interface/Turkey.h"
#include <memory>

class DuckAdapter : public Turkey
{
public:
    explicit DuckAdapter(std::shared_ptr<const Duck> duck);
    virtual ~DuckAdapter() = default;

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

private:
    std::shared_ptr<const Duck> _duck {};
};