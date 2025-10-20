#include "HottubOnCommand.h"
#include <iostream>

HottubOnCommand::HottubOnCommand(const std::shared_ptr<const Hottub>& hottub)
    : _hottub(hottub)
{
}

HottubOnCommand::~HottubOnCommand() = default;

void HottubOnCommand::execute() const
{
    if (_hottub.use_count()) {
        _hottub.lock()->on();
        _hottub.lock()->heat();
        _hottub.lock()->bubblesOn();
    } else
        std::cout << "device is broken" << std::endl;
}