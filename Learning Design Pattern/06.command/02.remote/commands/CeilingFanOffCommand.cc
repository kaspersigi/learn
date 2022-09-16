#include "CeilingFanOffCommand.h"

CeilingFanOffCommand::CeilingFanOffCommand(const CeilingFan* ceilingFan)
{
    _ceilingFan = std::shared_ptr<const CeilingFan>(ceilingFan);
}

void CeilingFanOffCommand::execute() const
{
    _ceilingFan->off();
}