#include "ChicagoStyleVeggiePizza.h"

ChicagoStyleVeggiePizza::ChicagoStyleVeggiePizza()
{
    _name = "Chicago Deep Dish Veggie Pizza";
    _dough = "Extra Thick Crust Dough";
    _sauce = "Plum Tomato Sauce";
    _toppings.push_back("Shredded Mozzarella Cheese");
    _toppings.push_back("Black Olives");
    _toppings.push_back("Spinach");
    _toppings.push_back("Eggplant");
}

void ChicagoStyleVeggiePizza::cut() const { std::cout << "Cutting the pizza into square slices" << std::endl; }