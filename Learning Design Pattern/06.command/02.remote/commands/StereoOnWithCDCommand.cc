#include "StereoOnWithCDCommand.h"

StereoOnWithCDCommand::StereoOnWithCDCommand(const Stereo* stereo)
{
    _stereo = std::shared_ptr<const Stereo>(stereo);
}

void StereoOnWithCDCommand::execute() const
{
    _stereo->on();
    _stereo->setCD();
    _stereo->setVolume(11);
}