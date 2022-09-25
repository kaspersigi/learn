#pragma once

#include "../interface/CaffeineBeverage.h"

class Tea : public CaffeineBeverage {
public:
    Tea() = default;
    ~Tea() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;

protected:
    Tea(const Tea&) = delete;
    Tea(Tea&&) = delete;
    Tea& operator=(const Tea&) = delete;
    Tea& operator=(Tea&&) = delete;
};