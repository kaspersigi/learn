#include "ClamPizza.h"

ClamPizza::ClamPizza(PizzaIngredientFactory* ingredientFactory)
    : _ingredientFactory(ingredientFactory)
{
}

void ClamPizza::prepare() const
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = std::shared_ptr<Dough>(_ingredientFactory->createDough());
    _sauce = std::shared_ptr<Sauce>(_ingredientFactory->createSauce());
    _cheese = std::shared_ptr<Cheese>(_ingredientFactory->createCheese());
    _clam = std::shared_ptr<Clams>(_ingredientFactory->createClams());
}