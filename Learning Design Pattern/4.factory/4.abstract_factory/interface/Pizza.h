#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Dough;
class Sauce;
class Veggies;
class Cheese;
class Pepperoni;
class Clams;

class Pizza {
public:
    virtual ~Pizza();

protected:
    Pizza() = default;
    Pizza(const Pizza&) = delete;
    Pizza(Pizza&&) = delete;
    Pizza& operator=(const Pizza&) = delete;
    Pizza& operator=(Pizza&&) = delete;

protected:
    std::shared_ptr<Dough> _dough;
    std::shared_ptr<Sauce> _sauce;
    std::vector<Veggies*> _veggies;
    std::shared_ptr<Cheese> _cheese;
    std::shared_ptr<Pepperoni> _pepperoni;
    std::shared_ptr<Clams> _clam;

private:
    std::string _name;

public:
    virtual void prepare() const = 0;
    virtual void bake() const;
    virtual void cut() const;
    virtual void box() const;
    std::string getName() const;
    void setName(std::string name);
    std::string toShow() const;
};