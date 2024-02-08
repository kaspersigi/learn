#pragma once

#include "../interface/Iterator.hpp"
#include "../interface/MenuItem.h"

class DinerMenuIterator : public Iterator<MenuItem> {
public:
    explicit DinerMenuIterator(MenuItem* item);
    explicit DinerMenuIterator(std::nullptr_t) = delete;
    virtual ~DinerMenuIterator() = default;

protected:
    DinerMenuIterator(const DinerMenuIterator&) = delete;
    DinerMenuIterator(DinerMenuIterator&&) = delete;
    DinerMenuIterator& operator=(const DinerMenuIterator&) = delete;
    DinerMenuIterator& operator=(DinerMenuIterator&&) = delete;
};