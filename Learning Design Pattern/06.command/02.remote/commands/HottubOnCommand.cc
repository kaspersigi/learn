#include "HottubOnCommand.h"

HottubOnCommand::HottubOnCommand(const Hottub* hottub)
{
    _hottub = std::shared_ptr<const Hottub>(hottub);
}

void HottubOnCommand::execute() const
{
    _hottub->on();
    _hottub->heat();
    _hottub->bubblesOn();
}