#pragma once

#include "../interface/Iterator.hpp"
#include "../interface/MenuItem.h"

class PancakeHouseMenuIterator : public Iterator<MenuItem> {
public:
    explicit PancakeHouseMenuIterator(MenuItem* item);
    virtual ~PancakeHouseMenuIterator() = default;

protected:
    PancakeHouseMenuIterator(const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator(PancakeHouseMenuIterator&&) = delete;
    PancakeHouseMenuIterator& operator=(const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator& operator=(PancakeHouseMenuIterator&&) = delete;
};