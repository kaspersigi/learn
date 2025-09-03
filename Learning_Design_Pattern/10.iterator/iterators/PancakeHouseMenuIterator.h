#pragma once

#include "../interface/Menu.h"
#include <vector>

class PancakeHouseMenuIterator : public Iterator<MenuItem>
{
public:
    explicit PancakeHouseMenuIterator(std::vector<std::shared_ptr<MenuItem>> items);
    virtual ~PancakeHouseMenuIterator() = default;

    virtual std::shared_ptr<MenuItem> next() const override;
    virtual bool hasNext() const override;

protected:
    PancakeHouseMenuIterator(const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator(PancakeHouseMenuIterator&&) = delete;
    PancakeHouseMenuIterator& operator = (const PancakeHouseMenuIterator&) = delete;
    PancakeHouseMenuIterator& operator = (PancakeHouseMenuIterator&&) = delete;

private:
    std::vector<std::shared_ptr<MenuItem>> _items {};
    mutable int _position { 0 };
};