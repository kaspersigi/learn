#pragma once

#include "../interface/Pizza.h"
#include <memory>

class PizzaIngredientFactory;

class VeggiePizza : public Pizza {
public:
    explicit VeggiePizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit VeggiePizza(std::nullptr_t) = delete;
    ~VeggiePizza() override;

    void prepare() override;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};