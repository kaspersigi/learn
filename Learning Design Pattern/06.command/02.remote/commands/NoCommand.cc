#include "NoCommand.h"
#include <iostream>

void NoCommand::execute() const { std::cout << "do nothing" << std::endl; }