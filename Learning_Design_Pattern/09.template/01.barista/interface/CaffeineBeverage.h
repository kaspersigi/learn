#pragma once

class CaffeineBeverage
{
public:
    CaffeineBeverage() = default;

    virtual void prepareRecipe();

protected:
    virtual ~CaffeineBeverage() = default;
    CaffeineBeverage(const CaffeineBeverage&) = delete;
    CaffeineBeverage(CaffeineBeverage&&) = delete;
    CaffeineBeverage& operator = (const CaffeineBeverage&) = delete;
    CaffeineBeverage& operator = (CaffeineBeverage&&) = delete;

    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;

private:
    void boilWater() const;
    void pourInCup() const;
};
