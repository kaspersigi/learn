#include "Decaf.h"

Decaf::Decaf() { _description = std::string("Decaf Coffee"); }

double Decaf::cost() const { return 1.05; }