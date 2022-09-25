#include "DinerMenuIterator.h"

DinerMenuIterator::DinerMenuIterator(MenuItem** items)
    : _items(items)
{
}

MenuItem* DinerMenuIterator::next() const
{
    MenuItem* menuItem = _items[_position];
    _position++;
    return menuItem;
}

bool DinerMenuIterator::hasNext() const { return _items[_position] ? true : false; }