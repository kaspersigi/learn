#pragma once

#include "../interface/Menu.h"

class DinerMenuIterator : public Iterator<MenuItem> {
public:
    explicit DinerMenuIterator(MenuItem** items);
    explicit DinerMenuIterator(std::nullptr_t) = delete;
    ~DinerMenuIterator() = default;

    virtual MenuItem* next() const override;
    virtual bool hasNext() const override;

protected:
    DinerMenuIterator(const DinerMenuIterator&) = delete;
    DinerMenuIterator(DinerMenuIterator&&) = delete;
    DinerMenuIterator& operator=(const DinerMenuIterator&) = delete;
    DinerMenuIterator& operator=(DinerMenuIterator&&) = delete;

private:
    MenuItem** _items { nullptr };
    mutable int _position { 0 };
};