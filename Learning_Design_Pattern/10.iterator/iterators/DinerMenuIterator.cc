#include "DinerMenuIterator.h"

DinerMenuIterator::DinerMenuIterator(const std::vector<std::shared_ptr<MenuItem>>& items)
    : _items(items)
{
}

const MenuItem& DinerMenuIterator::next() const
{
    auto& menuItem = _items[_position];
    _position++;
    return *menuItem;
}

bool DinerMenuIterator::hasNext() const { return _position < _items.size(); }