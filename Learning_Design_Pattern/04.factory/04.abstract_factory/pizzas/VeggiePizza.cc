#include "VeggiePizza.h"
#include <iostream>

VeggiePizza::VeggiePizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

void VeggiePizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
    if (_veggies.empty())
        _veggies = _ingredientFactory->createVeggies();
}