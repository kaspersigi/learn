#include "PancakeHouseMenuIterator.h"

PancakeHouseMenuIterator::PancakeHouseMenuIterator(std::vector<std::shared_ptr<MenuItem>> items)
    : _items(items)
{
}

const MenuItem& PancakeHouseMenuIterator::next() const
{
    auto& menuItem = _items[_position];
    _position++;
    return *menuItem;
}

bool PancakeHouseMenuIterator::hasNext() const { return _position < _items.size(); }