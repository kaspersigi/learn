#include "HottubOffCommand.h"
#include <iostream>

HottubOffCommand::HottubOffCommand(std::shared_ptr<const Hottub> hottub)
    : _hottub(hottub)
{
}

void HottubOffCommand::execute() const
{
    if (_hottub.use_count()) {
        _hottub.lock()->cool();
        _hottub.lock()->off();
    } else
        std::cout << "device is broken" << std::endl;
}