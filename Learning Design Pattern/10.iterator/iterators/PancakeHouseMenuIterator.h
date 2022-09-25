#pragma once

#include "../interface/Menu.h"
#include <vector>

class PancakeHouseMenuIterator : public Iterator<MenuItem> {
public:
    explicit PancakeHouseMenuIterator(std::vector<MenuItem*> items);
    ~PancakeHouseMenuIterator() = default;

    virtual MenuItem* next() const override;
    virtual bool hasNext() const override;

protected:
    PancakeHouseMenuIterator(const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator(PancakeHouseMenuIterator&&) = delete;
    PancakeHouseMenuIterator& operator=(const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator& operator=(PancakeHouseMenuIterator&&) = delete;

private:
    std::vector<MenuItem*> _items {};
    mutable int _position { 0 };
};