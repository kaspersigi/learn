#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Cheese.h"
#include "Clams.h"
#include "Dough.h"
#include "Pepperoni.h"
#include "Sauce.h"
#include "Veggies.h"

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
    mutable std::shared_ptr<Cheese> _cheese;
    mutable std::shared_ptr<Clams> _clam;
    mutable std::shared_ptr<Dough> _dough;
    mutable std::shared_ptr<Pepperoni> _pepperoni;
    mutable std::shared_ptr<Sauce> _sauce;
    mutable std::vector<Veggies*> _veggies;

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