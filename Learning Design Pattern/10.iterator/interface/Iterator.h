#pragma once

template <class T>
class Iterator {

public:
    virtual ~Iterator() = default;

    virtual bool hasNext() const = 0;
    virtual T* next() const = 0;

protected:
    Iterator() = default;
    Iterator(const Iterator&) = delete;
    Iterator(Iterator&&) = delete;
    Iterator& operator=(const Iterator&) = delete;
    Iterator& operator=(Iterator&&) = delete;
};