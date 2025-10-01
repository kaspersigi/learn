#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class VeggiePizza : public Pizza
{
public:
    explicit VeggiePizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit VeggiePizza(std::nullptr_t) = delete;
    virtual ~VeggiePizza() = default;

    void prepare() const;

protected:
    VeggiePizza(const VeggiePizza&) = delete;
    VeggiePizza(VeggiePizza&&) = delete;
    VeggiePizza& operator = (const VeggiePizza&) = delete;
    VeggiePizza& operator = (VeggiePizza&&) = delete;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};