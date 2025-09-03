#pragma once

#include <memory>

class ChocolateBoiler
{
public:
    ~ChocolateBoiler();
    static std::shared_ptr<ChocolateBoiler> getInstance();

    bool isEmpty() const;
    bool isBoiled() const;
    void fill();
    void drain();
    void boil();

protected:
    ChocolateBoiler() = default;
    ChocolateBoiler(const ChocolateBoiler&) = delete;
    ChocolateBoiler(ChocolateBoiler&&) = delete;
    ChocolateBoiler& operator = (const ChocolateBoiler&) = delete;
    ChocolateBoiler& operator = (ChocolateBoiler&&) = delete;

private:
    static std::shared_ptr<ChocolateBoiler> _uniqueInstance;
    bool _empty = true;
    bool _boiled = false;
};