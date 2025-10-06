#pragma once

#include "../interface/Menu.h"
#include <vector>

class DinerMenuIterator : public Iterator<MenuItem>
{
public:
    explicit DinerMenuIterator(const std::vector<std::shared_ptr<MenuItem>>& items);
    explicit DinerMenuIterator(std::nullptr_t) = delete;
    virtual ~DinerMenuIterator() = default;

    virtual const MenuItem& next() const override;
    virtual bool hasNext() const override;

private:
    const std::vector<std::shared_ptr<MenuItem>>& _items;
    mutable size_t _position { 0 };
};