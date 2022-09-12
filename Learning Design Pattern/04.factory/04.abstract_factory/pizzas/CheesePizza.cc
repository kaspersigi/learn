#include "CheesePizza.h"

CheesePizza::CheesePizza(PizzaIngredientFactory* ingredientFactory)
    : _ingredientFactory(ingredientFactory)
{
}

void CheesePizza::prepare() const
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = std::shared_ptr<Dough>(_ingredientFactory->createDough());
    _sauce = std::shared_ptr<Sauce>(_ingredientFactory->createSauce());
    _cheese = std::shared_ptr<Cheese>(_ingredientFactory->createCheese());
}