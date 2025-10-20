#include "StereoOffCommand.h"
#include <iostream>

StereoOffCommand::StereoOffCommand(const std::shared_ptr<const Stereo>& stereo)
    : _stereo(stereo)
{
}

StereoOffCommand::~StereoOffCommand() = default;

void StereoOffCommand::execute() const
{
    if (_stereo.use_count())
        _stereo.lock()->off();
    else
        std::cout << "device is broken" << std::endl;
}