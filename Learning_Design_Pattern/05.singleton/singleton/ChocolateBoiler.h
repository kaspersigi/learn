#pragma once

#include "NonCopyable.h"

class ChocolateBoiler : public NonCopyable {
public:
    static ChocolateBoiler& getInstance();

    bool isEmpty() const;
    bool isBoiled() const;
    void fill();
    void drain();
    void boil();

private:
    ChocolateBoiler() = default;
    ~ChocolateBoiler() = default;

    bool _empty = true;
    bool _boiled = false;
};