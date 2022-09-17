#include "CeilingFanOffCommand.h"
#include <iostream>

CeilingFanOffCommand::CeilingFanOffCommand(std::shared_ptr<const CeilingFan> ceilingFan)
    : _ceilingFan(ceilingFan)
{
}

void CeilingFanOffCommand::execute() const
{
    if (_ceilingFan.use_count())
        _ceilingFan.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}