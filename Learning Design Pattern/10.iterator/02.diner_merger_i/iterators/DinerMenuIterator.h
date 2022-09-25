#pragma once

#include "../interface/Menu.h"

class DinerMenuIterator : public Iterator<MenuItem> {
public:
    explicit DinerMenuIterator(std::shared_ptr<MenuItem>* items);
    explicit DinerMenuIterator(std::nullptr_t) = delete;
    ~DinerMenuIterator() = default;

    virtual std::shared_ptr<MenuItem> next() const override;
    virtual bool hasNext() const override;

protected:
    DinerMenuIterator(const DinerMenuIterator&) = delete;
    DinerMenuIterator(DinerMenuIterator&&) = delete;
    DinerMenuIterator& operator=(const DinerMenuIterator&) = delete;
    DinerMenuIterator& operator=(DinerMenuIterator&&) = delete;

private:
    std::shared_ptr<MenuItem>* _items { nullptr };
    mutable int _position { 0 };
};