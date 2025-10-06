#pragma once

#include "Iterator.h"
#include "MenuItem.h"
#include "NonCopyable.h"
#include <memory>

class Menu : public NonCopyable
{
public:
    virtual ~Menu() = default;

    virtual std::unique_ptr<Iterator<MenuItem>> createIterator() const = 0;

protected:
    Menu() = default;
};