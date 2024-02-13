#include "DinerMenuIterator.h"

DinerMenuIterator::DinerMenuIterator(std::shared_ptr<MenuItem>* items)
    : _items(items)
{
}

std::shared_ptr<MenuItem> DinerMenuIterator::next() const
{
    auto menuItem = _items[_position];
    _position++;
    return menuItem;
}

bool DinerMenuIterator::hasNext() const { return _items[_position] ? true : false; }