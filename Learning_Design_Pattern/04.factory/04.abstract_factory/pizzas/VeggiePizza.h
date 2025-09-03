#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class VeggiePizza : public Pizza
{
public:
    explicit VeggiePizza(PizzaIngredientFactory * ingredientFactory);
    explicit VeggiePizza(std::nullptr_t) = delete;
    virtual ~VeggiePizza() = default;

    void prepare() const;

protected:
    VeggiePizza(const VeggiePizza&) = delete;
    VeggiePizza(VeggiePizza&&) = delete;
    VeggiePizza& operator = (const VeggiePizza&) = delete;
    VeggiePizza& operator = (VeggiePizza&&) = delete;

private:
    mutable std::shared_ptr<PizzaIngredientFactory> _ingredientFactory {};
};