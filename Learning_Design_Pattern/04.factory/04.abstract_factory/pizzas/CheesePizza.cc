#include "CheesePizza.h"
#include "../interface/PizzaIngredientFactory.h"
#include <iostream>

CheesePizza::CheesePizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

CheesePizza::~CheesePizza() = default;

void CheesePizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
}