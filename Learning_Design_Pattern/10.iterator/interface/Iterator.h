#pragma once

#include "NonCopyable.h"
#include <memory>

template<class T> class Iterator : public NonCopyable
{
public:
    virtual ~Iterator() = default;

    virtual bool hasNext() const = 0;
    virtual const T& next() const = 0;

protected:
    Iterator() = default;
};