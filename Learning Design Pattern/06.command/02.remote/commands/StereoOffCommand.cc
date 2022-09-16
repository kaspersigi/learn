#include "StereoOffCommand.h"

StereoOffCommand::StereoOffCommand(const Stereo* stereo)
{
    _stereo = std::shared_ptr<const Stereo>(stereo);
}

void StereoOffCommand::execute() const
{
    _stereo->off();
}