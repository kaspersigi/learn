#include "CeilingFanOnCommand.h"
#include <iostream>

CeilingFanOnCommand::CeilingFanOnCommand(const std::shared_ptr<const CeilingFan>& ceilingFan)
{
    _ceilingFan = std::shared_ptr<const CeilingFan>(ceilingFan);
}

CeilingFanOnCommand::~CeilingFanOnCommand() = default;

void CeilingFanOnCommand::execute() const
{
    if (_ceilingFan.use_count())
        _ceilingFan.lock()->high();
    else
        std::cout << "device is broken" << std::endl;
}