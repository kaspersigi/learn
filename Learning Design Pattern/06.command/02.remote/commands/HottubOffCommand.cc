#include "HottubOffCommand.h"

HottubOffCommand::HottubOffCommand(const Hottub* hottub)
{
    _hottub = std::shared_ptr<const Hottub>(hottub);
}

void HottubOffCommand::execute() const
{
    _hottub->cool();
    _hottub->off();
}