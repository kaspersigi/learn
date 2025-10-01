#include "CheesePizza.h"

CheesePizza::CheesePizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

void CheesePizza::prepare() const
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = std::shared_ptr<Dough>(_ingredientFactory->createDough());
    _sauce = std::shared_ptr<Sauce>(_ingredientFactory->createSauce());
    _cheese = std::shared_ptr<Cheese>(_ingredientFactory->createCheese());
}