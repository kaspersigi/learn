#include "ChicagoStyleClamPizza.h"

ChicagoStyleClamPizza::ChicagoStyleClamPizza()
{
    _name = "Chicago Style Clam Pizza";
    _dough = "Extra Thick Crust Dough";
    _sauce = "Plum Tomato Sauce";
    _toppings.push_back("Shredded Mozzarella Cheese");
    _toppings.push_back("Frozen Clams from Chesapeake Bay");
}

void ChicagoStyleClamPizza::cut() const { std::cout << "Cutting the pizza into square slices" << std::endl; }