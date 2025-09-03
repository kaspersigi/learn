#pragma once

class DisplayElement
{
public:
    virtual ~DisplayElement() = default;

    virtual void display() const = 0;

protected:
    DisplayElement() = default;
    DisplayElement(const DisplayElement&) = delete;
    DisplayElement(DisplayElement&&) = delete;
    DisplayElement& operator = (const DisplayElement&) = delete;
    DisplayElement& operator = (DisplayElement&&) = delete;
};