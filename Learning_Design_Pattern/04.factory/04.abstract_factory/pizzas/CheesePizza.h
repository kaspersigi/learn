#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class CheesePizza : public Pizza
{
public:
    explicit CheesePizza(PizzaIngredientFactory * ingredientFactory);
    explicit CheesePizza(std::nullptr_t) = delete;
    virtual ~CheesePizza() = default;

    void prepare() const;

protected:
    CheesePizza(const CheesePizza&) = delete;
    CheesePizza(CheesePizza&&) = delete;
    CheesePizza& operator = (const CheesePizza&) = delete;
    CheesePizza& operator = (CheesePizza&&) = delete;

private:
    mutable std::shared_ptr<PizzaIngredientFactory> _ingredientFactory {};
};