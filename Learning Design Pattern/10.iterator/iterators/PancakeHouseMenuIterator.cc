#include "PancakeHouseMenuIterator.h"

PancakeHouseMenuIterator::PancakeHouseMenuIterator(std::vector<MenuItem*> items)
    : _items(items)
{
}

MenuItem* PancakeHouseMenuIterator::next() const
{
    MenuItem* menuItem = _items[_position];
    _position++;
    return menuItem;
}

bool PancakeHouseMenuIterator::hasNext() const { return (_position < _items.size()) ? true : false; }