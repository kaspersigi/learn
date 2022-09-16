#include "CeilingFanOnCommand.h"

CeilingFanOnCommand::CeilingFanOnCommand(const CeilingFan* ceilingFan)
{
    _ceilingFan = std::shared_ptr<const CeilingFan>(ceilingFan);
}

void CeilingFanOnCommand::execute() const
{
    _ceilingFan->high();
}