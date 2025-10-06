#include "CheesePizza.h"
#include <iostream>

CheesePizza::CheesePizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

void CheesePizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
}