#pragma once

class Interface
{
protected:
    Interface();
    virtual ~Interface();

    Interface(const Interface&) = delete;
    Interface(Interface&&) = delete;
    Interface& operator = (const Interface&) = delete;
    Interface& operator = (Interface&&) = delete;
};