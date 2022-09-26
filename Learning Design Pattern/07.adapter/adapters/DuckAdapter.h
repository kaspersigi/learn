#pragma once

#include "../interface/Duck.h"
#include "../interface/Turkey.h"
#include <memory>

class DuckAdapter : public Turkey {
public:
    explicit DuckAdapter(const Duck* duck);
    virtual ~DuckAdapter() = default;

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

protected:
    DuckAdapter(const DuckAdapter&) = delete;
    DuckAdapter(DuckAdapter&&) = delete;
    DuckAdapter& operator=(const DuckAdapter&) = delete;
    DuckAdapter& operator=(DuckAdapter&&) = delete;

private:
    std::shared_ptr<const Duck> _duck {};
};