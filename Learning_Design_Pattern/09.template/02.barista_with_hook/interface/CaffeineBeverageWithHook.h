#pragma once

class CaffeineBeverageWithHook {
public:
    CaffeineBeverageWithHook() = default;

    virtual void prepareRecipe();

protected:
    virtual ~CaffeineBeverageWithHook() = default;
    CaffeineBeverageWithHook(const CaffeineBeverageWithHook&) = delete;
    CaffeineBeverageWithHook(CaffeineBeverageWithHook&&) = delete;
    CaffeineBeverageWithHook& operator=(const CaffeineBeverageWithHook&) = delete;
    CaffeineBeverageWithHook& operator=(CaffeineBeverageWithHook&&) = delete;

    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;
    virtual bool customerWantsCondiments() const;

private:
    void boilWater() const;
    void pourInCup() const;
};
