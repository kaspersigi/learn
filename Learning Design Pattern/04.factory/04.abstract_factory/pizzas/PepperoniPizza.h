#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class PepperoniPizza : public Pizza {
public:
    explicit PepperoniPizza(PizzaIngredientFactory* ingredientFactory);
    explicit PepperoniPizza(std::nullptr_t) = delete;
    virtual ~PepperoniPizza() = default;

    void prepare() const;

protected:
    PepperoniPizza(const PepperoniPizza&) = delete;
    PepperoniPizza(PepperoniPizza&&) = delete;
    PepperoniPizza& operator=(const PepperoniPizza&) = delete;
    PepperoniPizza& operator=(PepperoniPizza&&) = delete;

private:
    mutable std::shared_ptr<PizzaIngredientFactory> _ingredientFactory;
};