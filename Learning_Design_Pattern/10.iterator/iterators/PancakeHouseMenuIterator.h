#pragma once

#include "../interface/Menu.h"
#include <vector>

class PancakeHouseMenuIterator : public Iterator<MenuItem>
{
public:
    explicit PancakeHouseMenuIterator(std::vector<std::shared_ptr<MenuItem>> items);
    virtual ~PancakeHouseMenuIterator() = default;

    virtual const MenuItem& next() const override;
    virtual bool hasNext() const override;

private:
    std::vector<std::shared_ptr<MenuItem>> _items {};
    mutable size_t _position { 0 };
};