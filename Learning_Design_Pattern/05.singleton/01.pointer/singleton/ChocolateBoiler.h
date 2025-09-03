#pragma once

class ChocolateBoiler
{
public:
    ~ChocolateBoiler();
    static ChocolateBoiler* getInstance();

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
    static ChocolateBoiler* _uniqueInstance;
    bool _empty = true;
    bool _boiled = false;
};