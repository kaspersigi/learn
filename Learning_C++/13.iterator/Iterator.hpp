#pragma once

template <typename T>
class Iterator {
public:
    Iterator(T* data);
    ~Iterator() = default;
    Iterator(const Iterator& iterator);
    Iterator(Iterator&& Iterator);
    Iterator& operator=(const Iterator& iterator);
    Iterator& operator=(Iterator&& iterator);

    T& operator*() const;
    T* operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    T& operator[](int n) const;
    Iterator& operator+=(int n);
    Iterator operator+(int n) const;
    Iterator& operator-=(int n);
    Iterator operator-(int n) const;
    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;
    bool operator<(const Iterator& iterator) const;
    bool operator>(const Iterator& iterator) const;
    bool operator<=(const Iterator& iterator) const;
    bool operator>=(const Iterator& iterator) const;
    T* base() const;

protected:
    T* _current = nullptr;
};

template <typename T>
Iterator<T>::Iterator(T* data)
{
    _current = data;
}

template <typename T>
Iterator<T>::Iterator(const Iterator& iterator)
{
    _current = iterator._current;
}

template <typename T>
Iterator<T>::Iterator(Iterator&& iterator)
{
    _current = iterator._current;
    iterator._current = nullptr;
}

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator& iterator)
{
    _current = iterator._current;
}

template <typename T>
Iterator<T>& Iterator<T>::operator=(Iterator&& iterator)
{
    _current = iterator._current;
    iterator._current = nullptr;
}

template <typename T>
T& Iterator<T>::operator*() const { return *_current; }

template <typename T>
T* Iterator<T>::operator->() const { return _current; }

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
    ++_current;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    return Iterator(++_current);
}

template <typename T>
Iterator<T>& Iterator<T>::operator--()
{
    --_current;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int)
{
    return Iterator(--_current);
}

template <typename T>
T& Iterator<T>::operator[](int n) const { return _current[n]; }

template <typename T>
Iterator<T>& Iterator<T>::operator+=(int n)
{
    _current += n;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator+(int n) const { return Iterator(_current + n); }

template <typename T>
Iterator<T>& Iterator<T>::operator-=(int n)
{
    _current -= n;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator-(int n) const { return Iterator(_current - n); }

template <typename T>
bool Iterator<T>::operator==(const Iterator& iterator) const { return _current == iterator._current; }

template <typename T>
bool Iterator<T>::operator!=(const Iterator& iterator) const { return _current != iterator._current; }

template <typename T>
bool Iterator<T>::operator<(const Iterator& iterator) const { return _current < iterator._current; }

template <typename T>
bool Iterator<T>::operator>(const Iterator& iterator) const { return _current > iterator._current; }

template <typename T>
bool Iterator<T>::operator<=(const Iterator& iterator) const { return _current < iterator._current; }

template <typename T>
bool Iterator<T>::operator>=(const Iterator& iterator) const { return _current > iterator._current; }

template <typename T>
T* Iterator<T>::base() const { return _current; }